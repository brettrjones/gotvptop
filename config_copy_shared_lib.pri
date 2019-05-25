

#copy to local directory so can easily be linked to

win:{
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.dll) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE})
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

!win:{
    copydata.commands = $(COPY_DIR) $$shell_path($$OUT_PWD/*.so) $$shell_path($$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE})
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

!android:{
    #rename and move android lib to android/lib/target arch directory
    SHARED_ANDROID_SRC_NAME = ""
    SHARED_ANDROID_SRC_DIR = ""
    SHARED_ANDROID_DEST_NAME = ""

    SHARED_ANDROID_LIB_COPY_CMD = ""

    CONFIG(debug, debug|release){
        SHARED_ANDROID_SRC_DIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
     }

     CONFIG(release, debug|release){
        SHARED_ANDROID_SRC_DIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/$${BUILD_TYPE}
     }


    CONFIG(debug, debug|release){
        SHARED_ANDROID_SRC_NAME = lib$${TARGET_NAME}_d.so
        SHARED_ANDROID_DEST_NAME = lib$${TARGET_NAME}_d.so
     }

     CONFIG(release, debug|release){
        SHARED_ANDROID_SRC_NAME = lib$${TARGET_NAME}.so
        SHARED_ANDROID_DEST_NAME = lib$${TARGET_NAME}.so
     }

    SHARED_ANDROID_LIB_COPY_CMD = $${COPY_KEYWORD} $${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME} $${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME}
    contains(QMAKE_HOST.os,Windows):
    {
        SHARED_ANDROID_LIB_COPY_CMD ~= s,/,\\,g # replace / with \
    }

    #message("**android dll cmd $${SHARED_ANDROID_LIB_COPY_CMD}")

    QMAKE_POST_LINK += $${SHARED_ANDROID_LIB_COPY_CMD}
}





