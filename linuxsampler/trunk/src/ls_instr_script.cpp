/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This program is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "common/global.h"
#include "scriptvm/ScriptVM.h"
#include "shell/CFmt.h"

/*
  This command line tool is currently merely for development and testing
  purposes, regarding the real-time instrument script feature of the sampler.
  You can use this command line application like this:

  ls_instr_script < src/scriptvm/examples/helloworld.txt

  Which will peform 3 things:

  1. Parses the given instrument script and prints any parser errors or
     warnings.
  2. It dumps the parsed VM tree (only interesting for LS developers).
  3. If there were not parser errors, it will run each event handler defined in
     the script.
 */

using namespace LinuxSampler;

int main() {
    ScriptVM vm;
    VMParserContext* parserContext = vm.loadScript(&std::cin);

    std::vector<ParserIssue> errors = parserContext->errors();
    std::vector<ParserIssue> warnings = parserContext->warnings();
    std::vector<ParserIssue> issues = parserContext->issues();
    if (warnings.empty() && errors.empty()) {
        CFmt fmt; fmt.green();
        printf("EOF. Script parse completed successfully (no errors, no warnings).\n");
    } else if (!errors.empty()) {
        CFmt fmt; fmt.red();
        printf("EOF. Script parse completed with issues (%d errors, %d warnings):\n",
               errors.size(), warnings.size());
    } else {
        CFmt fmt; fmt.yellow();
        printf("EOF. Script parse completed with issues (%d errors, %d warnings):\n",
               errors.size(), warnings.size());
    }
    for (int i = 0; i < issues.size(); ++i) {
        CFmt fmt;
        if (issues[i].isWrn()) fmt.yellow();
        else if (issues[i].isErr()) fmt.red();
        issues[i].dump();
    }

    printf("[Dumping parsed VM tree]\n");
    vm.dumpParsedScript(parserContext);
    printf("[End of parsed VM tree]\n");

    if (!errors.empty()) {
        if (parserContext) delete parserContext;
        return -1;
    }

    if (!parserContext->eventHandler(0)) {
        printf("No event handler exists. So nothing to execute.\n");
        if (parserContext) delete parserContext;
        return 0;
    }

    printf("Preparing execution of script.\n");
    VMExecContext* execContext = vm.createExecContext(parserContext);
    for (int i = 0; parserContext->eventHandler(i); ++i) {
        VMEventHandler* handler = parserContext->eventHandler(i);
        printf("[Running event handler '%s']\n", handler->eventHandlerName().c_str());
        VMExecStatus_t result = vm.exec(parserContext, execContext, handler);
        CFmt fmt;
        if (result & VM_EXEC_ERROR) {
            fmt.red();
            printf("[Event handler '%s' finished with ERROR status]\n", handler->eventHandlerName().c_str());
        } else if (result & VM_EXEC_SUSPENDED) {
            fmt.yellow();
            printf("[Event handler '%s' returned with SUSPENDED status: %d microseconds]\n",
                   handler->eventHandlerName().c_str(), execContext->suspensionTimeMicroseconds());
        } else if (!(result & VM_EXEC_RUNNING)) {
            fmt.green();
            printf("[Event handler '%s' finished with SUCCESS status]\n", handler->eventHandlerName().c_str());
        } else if (result & VM_EXEC_RUNNING) {
            fmt.cyan();
            printf("[Event handler '%s' finished with RUNNING status]\n", handler->eventHandlerName().c_str());
        } else {
            fmt.red();
            printf("[Event handler '%s' finished with UNKNOWN status]\n", handler->eventHandlerName().c_str());
        }
    }
    if (parserContext) delete parserContext;
    if (execContext) delete execContext;

    return 0;
}
