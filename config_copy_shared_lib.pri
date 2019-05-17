

#copy to local directory so can easily be linked to
 CONFIG(debug, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug)
 }

 CONFIG(release, debug|release){
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release)
 }

 first.depends = $(first) copydata
 export(first.depends)
 export(copydata.commands)
 QMAKE_EXTRA_TARGETS += first copydata


