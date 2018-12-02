TEMPLATE = subdirs

qtHaveModule(widgets): SUBDIRS += GoTvExample


qtHaveModule(opengl):!qtConfig(opengles2): SUBDIRS += opengl
