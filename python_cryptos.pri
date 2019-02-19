
contains( TARGET_CPU_BITS, 64 ) {
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include64
}

contains( TARGET_CPU_BITS, 32 ) {
    INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/include32
}

INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/modes
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/asn1
INCLUDEPATH += $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/crypto/evp


SOURCES += 	$$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl_algs.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/d1_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/d1_pkt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/d1_srtp.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s23_clnt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s23_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s23_meth.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s23_pkt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s23_srvr.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_clnt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_enc.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_meth.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_pkt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s2_srvr.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_both.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_cbc.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_clnt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_enc.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_meth.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_pkt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/s3_srvr.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_algs.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_asn1.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_cert.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_ciph.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_err.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_err2.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_rsa.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/ssl_sess.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_clnt.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_enc.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_lib.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_meth.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_reneg.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/t1_srvr.c \
    $$PWD/DependLibs/Python-2.7.14/externals/openssl-1.0.2k/ssl/tls_srp.c

