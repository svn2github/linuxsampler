/* *************************************************************************
 * Copyright (c) 2005 VMware, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * *************************************************************************/

#ifndef LIBVIEW_WRAP_LABEL_HH
#define LIBVIEW_WRAP_LABEL_HH


#include <gtkmm/label.h>


namespace view {


class WrapLabel
   : public Gtk::Label
{
public:
   WrapLabel(const Glib::ustring &text = "");

   void set_text(const Glib::ustring &str);
   void set_markup(const Glib::ustring &str);

protected:
   virtual void on_size_allocate(Gtk::Allocation &alloc);
   virtual void on_size_request(Gtk::Requisition *req);

private:
   void SetWrapWidth(size_t width);

   size_t mWrapWidth;
};


} /* namespace view */


#endif /* LIBVIEW_WRAP_LABEL_HH */
