
#rename and move python extention lib to bin directory
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

unix {
    CONFIG(debug, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}_d.so.1.0.0
        PYTHON_DEST_NAME = $${TARGET_NAME}_d.pyd
     }

     CONFIG(release, debug|release){
        PYTHON_SRC_NAME = lib$${TARGET_NAME}.so.1.0.0
        PYTHON_DEST_NAME = $${TARGET_NAME}.pyd
     }

    #copydata.commands = cp $${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME} $${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}
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

#target.path = DEST_PYTHON_DLL_DIR

#extra_install.path =$$target.path
#extra_install.files = PYTHON_DEST_NAME
message("**python dll copy src->$${PYTHON_SRC_DIR}/$${PYTHON_SRC_NAME}")
message("**python dll copy dest->$${DEST_PYTHON_DLL_DIR}/$${PYTHON_DEST_NAME}")

#copy to bin directory so works with app

# first.depends = $(first) copydata
# export(first.depends)
# export(copydata.commands)
# QMAKE_EXTRA_TARGETS += first copydata

QMAKE_POST_LINK += $$quote($${PYTHON_LIB_COPY_CMD})
