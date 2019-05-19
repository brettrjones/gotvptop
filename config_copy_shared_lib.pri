

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


android:{

    #rename and move android lib to android/lib/target arch directory
    SHARED_ANDROID_SRC_NAME = ""
    SHARED_ANDROID_SRC_DIR = ""
    SHARED_ANDROID_DEST_NAME = ""

    SHARED_ANDROID_LIB_COPY_CMD = ""

    CONFIG(debug, debug|release){
        SHARED_ANDROID_SRC_DIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
     }

     CONFIG(release, debug|release){
        SHARED_ANDROID_SRC_DIR = $$PWD/build-sharedlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
     }


    CONFIG(debug, debug|release){
        SHARED_ANDROID_SRC_NAME = lib$${TARGET_NAME}_d.so
        SHARED_ANDROID_DEST_NAME = lib$${TARGET_NAME}_d.so
     }

     CONFIG(release, debug|release){
        SHARED_ANDROID_SRC_NAME = lib$${TARGET_NAME}.so
        SHARED_ANDROID_DEST_NAME = lib$${TARGET_NAME}.so
     }

    SHARED_ANDROID_LIB_COPY_CMD = cp $${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME} $${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME}

    message("**android dll copy src->$${SHARED_ANDROID_SRC_DIR}/$${SHARED_ANDROID_SRC_NAME}")
    message("**android dll copy dest->$${DEST_EXE_DIR}/$${SHARED_ANDROID_DEST_NAME}")

    QMAKE_POST_LINK += $$quote($${SHARED_ANDROID_LIB_COPY_CMD})
}





