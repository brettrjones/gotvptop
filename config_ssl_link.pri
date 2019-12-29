

CONFIG(debug, debug|release){
    LIBS +=  $${DEST_SHARED_LIBS_DIR}/libssl_d.so
}

CONFIG(release, debug|release){
    LIBS +=  $${DEST_SHARED_LIBS_DIR}/libssl.so
}
