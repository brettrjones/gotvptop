TEMPLATE = subdirs

qtHaveModule(widgets): SUBDIRS += svgviewer


qtHaveModule(opengl):!qtConfig(opengles2): SUBDIRS += opengl
