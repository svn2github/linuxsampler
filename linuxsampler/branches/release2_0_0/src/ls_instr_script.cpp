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
#include "engines/common/InstrumentScriptVM.h"
#include "engines/gig/InstrumentScriptVM.h"
#include <iostream>

/*
  This command line tool is currently merely for development and testing
  purposes, regarding the real-time instrument script feature of the sampler.
  You can use this command line application like this:

  ls_instr_script core < src/scriptvm/examples/helloworld.txt

  Which will peform 3 things:

  1. Parses the given instrument script and prints any parser errors or
     warnings.
  2. It dumps the parsed VM tree (only interesting for LS developers).
  3. If there were not parser errors, it will run each event handler defined in
     the script.
 */

using namespace LinuxSampler;
using namespace std;

static void printUsage() {
    cout << "ls_instr_script - Parse real-time instrument script from stdin." << endl;
    cout << endl;
    cout << "Usage: ls_instr_script ENGINE" << endl;
    cout << endl;
    cout << "    ENGINE\n";
    cout << "        Either \"core\", \"gig\", \"sf2\" or \"sfz\"." << endl;
    cout << endl;
    cout << "If you pass \"core\" as argument, only the core language built-in" << endl;
    cout << "variables and functions are available. However in this particular" << endl;
    cout << "mode the program will not just parse the given script, but also" << endl;
    cout << "execute the event handlers. All other arguments for ENGINE provide" << endl;
    cout << "the sampler engine / sampler format specific additional built-in" << endl;
    cout << "variables and functions, however they wil not be executed by this" << endl;
    cout << "program." << endl;
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage();
        return -1;
    }
    String engine = argv[1];
    bool runScript = false;

    ScriptVM* vm;
    if (engine == "core") {
        vm = new ScriptVM;
        runScript = true;
    } else if (engine == "sf2" || engine == "sfz") {
        vm = new InstrumentScriptVM;
    } else if (engine == "gig") {
        vm = new gig::InstrumentScriptVM;
    } else {
        std::cerr << "Unknown ENGINE '" << engine << "'\n\n";
        printUsage();
        return -1;
    }

    VMParserContext* parserContext = vm->loadScript(&std::cin);

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
    vm->dumpParsedScript(parserContext);
    printf("[End of parsed VM tree]\n");

    if (!errors.empty()) {
        if (parserContext) delete parserContext;
        return -1;
    }

    if (!runScript) {
        return 0;
    }

    if (!parserContext->eventHandler(0)) {
        printf("No event handler exists. So nothing to execute.\n");
        if (parserContext) delete parserContext;
        return 0;
    }

    printf("Preparing execution of script.\n");
    VMExecContext* execContext = vm->createExecContext(parserContext);
    for (int i = 0; parserContext->eventHandler(i); ++i) {
        VMEventHandler* handler = parserContext->eventHandler(i);
        printf("[Running event handler '%s']\n", handler->eventHandlerName().c_str());
        VMExecStatus_t result = vm->exec(parserContext, execContext, handler);
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
    if (vm) delete vm;

    return 0;
}
