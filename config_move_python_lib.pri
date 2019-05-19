
#rename and move python extention lib to bin/Python directory
PYTHON_SRC_NAME = ""
PYTHON_SRC_DIR = ""
PYTHON_DEST_NAME = ""

PYTHON_LIB_COPY_CMD = ""

CONFIG(debug, debug|release){
    PYTHON_SRC_DIR = $$PWD/build-pythonlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/debug
 }

 CONFIG(release, debug|release){
    PYTHON_SRC_DIR = $$PWD/build-pythonlibs/$${TARGET_OS_NAME}/$${TARGET_ARCH_NAME}/release
 }

unix:!android {
    CONFIG(debug, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}_d.so.1.0.0
        PYTHON_DEST_NAME = $${TARGET_NAME}_d.pyd
     }

     CONFIG(release, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}.so.1.0.0
        PYTHON_DEST_NAME = $${TARGET_NAME}.pyd
     }

    PYTHON_LIB_COPY_CMD = cp $${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME} $${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}
}

android {
    CONFIG(debug, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}_d.so
        PYTHON_DEST_NAME = $${TARGET_NAME}_d.pyd
     }

     CONFIG(release, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}.so
        PYTHON_DEST_NAME = $${TARGET_NAME}.pyd
     }

    PYTHON_LIB_COPY_CMD = cp $${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME} $${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}
}

win32 {
    CONFIG(debug, debug|release){
        PYTHON_SRC_NAME = $${TARGET_NAME}_d.dll
        PYTHON_DEST_NAME = $${TARGET_NAME}_d.pyd
     }

     CONFIG(release, debug|release){
        PYTHON_SRC_NAME = $${TARGET_NAME}.dll
        PYTHON_DEST_NAME = $${TARGET_NAME}.pyd
     }

    #copydata.commands = copy $${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME} $${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}
    PYTHON_LIB_COPY_CMD = cp $${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME} $${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}
}

message("**python dll copy src->$${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME}")
message("**python dll copy dest->$${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}")

QMAKE_POST_LINK += $$quote($${PYTHON_LIB_COPY_CMD})
