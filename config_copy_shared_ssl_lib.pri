

#copy to local directory so can easily be linked to

win:{
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.dll) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE})
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

unix:!android:  {
    copydata.commands = $(COPY_DIR) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}) $$shell_path($${DEST_EXE_DIR})
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

android:{
    message(DESTDIR_SSL is $${DESTDIR})

    #rename and move android lib to android/libs/target arch directory
    SHARED_SSL_ANDROID_SRC_NAME = ""
    SHARED_SSL_ANDROID_SRC_DIR = ""
    SHARED_SSL_ANDROID_DEST_NAME = ""

    SHARED_SSL_ANDROID_LIB_COPY_CMD = ""

    SHARED_SSL_ANDROID_SRC_DIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
    contains(QMAKE_HOST.os,Windows){
        SHARED_SSL_ANDROID_SRC_DIR = $$OUT_PWD
    }

    message(OUT_PWD_DIR is $${OUT_PWD})
    message(SHARED_SSL_ANDROID_SRC_DIR is $${SHARED_SSL_ANDROID_SRC_DIR})

    CONFIG(debug, debug|release){
        SHARED_SSL_ANDROID_SRC_NAME = lib$${TARGET_NAME}_d.so
        SHARED_SSL_ANDROID_DEST_NAME = lib$${TARGET_NAME}_d.so
     }

     CONFIG(release, debug|release){
        SHARED_SSL_ANDROID_SRC_NAME = lib$${TARGET_NAME}.so
        SHARED_SSL_ANDROID_DEST_NAME = lib$${TARGET_NAME}.so
     }

    SHARED_SSL_ANDROID_LIB_COPY_CMD = cp -f $${SHARED_SSL_ANDROID_SRC_DIR}/$${SHARED_SSL_ANDROID_SRC_NAME} $${DEST_EXE_DIR}/$${SHARED_SSL_ANDROID_SRC_NAME}
    message(SSL CP COMMAND is $${SHARED_SSL_ANDROID_LIB_COPY_CMD})

    QMAKE_POST_LINK += $$quote($${SHARED_SSL_ANDROID_LIB_COPY_CMD})
#    contains(QMAKE_HOST.os,Windows){
#        #SHARED_ANDROID_LIB_COPY_CMD ~= s,/,\\,g # replace / with \
#        #work around that qmake DESTDIR and other commands do not work with android make on windows (Qt 5.12.2)
#        # copy built .so file to shared libs directory
         #path just has to be something that can stat successfully
#        bsharetarget.path = $$shell_quote($$shell_path($$PWD/dummyfileforqmakebug.txt))
#        bsharetarget.path = $${DEST_EXE_DIR}
#        export(bsharetarget.path)
#        bsharetarget.target = mytarget
#         bsharetarget.commands = @echo copy to shared lib $${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME} && $$quote(cp -f -R  $$quote( $$shell_path($$OUT_PWD/$$ {SHARED_ANDROID_SRC_NAME}) $$shell_path($${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_DEST_NAME})$$escape_expand(\n\t)))
#        bsharetarget.commands = $$quote($(COPY) $$shell_path($${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME}) $$shell_path($${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME})$$escape_expand(\n\t)))
#        export(bsharetarget.commands)
#        QMAKE_EXTRA_TARGETS += bsharetarget
        # copy built .so file to deploy libs directory
        #path just has to be something that can stat successfully
#        bsharetarget2.path = $$shell_quote($$shell_path($$PWD/dummyfileforqmakebug.txt))
#        bsharetarget2.target = mytarget2
#        export(bsharetarget2.path)
#        bsharetarget2.commands = @echo moving to $${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME} && $$quote(cp -f -R  $$quote( $$shell_path($${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME}) $$shell_path($${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME})$$escape_expand(\n\t)))
#        export(bsharetarget2.commands)

#        QMAKE_EXTRA_TARGETS += bsharetarget bsharetarget2
#        export(QMAKE_EXTRA_TARGETS)
#        INSTALLS += bpythontarget bpythontarget2

#    }

    #message("**android dll cmd $${SHARED_ANDROID_LIB_COPY_CMD}")

#    !contains(QMAKE_HOST.os,Windows){
#        QMAKE_POST_LINK += $${SHARED_ANDROID_LIB_COPY_CMD}
#QMAKE_POST_LINK += $$quote(cp -f $$shell_path($${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME}) $$shell_path($${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME})$))
#    }
}





