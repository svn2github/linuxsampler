docdir = $(datadir)/doc/$(PACKAGE)

doc_DATA = gigedit_quickstart.html style.css shot_whole_app.png \
	shot_default_group.png shot_new_dimension.png shot_add_sample.png \
	routing.png shot_amp1.png shot_amp2.png shot_filter1.png \
	shot_filter2.png

doc_sources = gigedit_quickstart.xml general_midi_drummap.sgm \
	mc505_midi_drummap.sgm from_scratch.sgm glossary.sgm keybindings.sgm \
	libgig.sgm see_also.sgm technical.sgm

EXTRA_DIST = $(doc_DATA) $(doc_sources)

gigedit_quickstart.html: $(doc_sources)
	xsltproc --output $@ \
	--stringparam html.stylesheet style.css \
	/usr/share/sgml/docbook/xsl-stylesheets/html/docbook.xsl \
	gigedit_quickstart.xml
