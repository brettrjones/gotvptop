DEFINES += LIBSSH_STATIC

INCLUDEPATH += $$PWD/DependLibs/libssh/

HEADERS += 	$$PWD/DependLibs/libssh/agent.h \
    $$PWD/DependLibs/libssh/auth.h \
    $$PWD/DependLibs/libssh/bignum.h \
    $$PWD/DependLibs/libssh/bind.h \
    $$PWD/DependLibs/libssh/blf.h \
    $$PWD/DependLibs/libssh/buffer.h \
    $$PWD/DependLibs/libssh/callbacks.h \
    $$PWD/DependLibs/libssh/channels.h \
    $$PWD/DependLibs/libssh/crc32.h \
    $$PWD/DependLibs/libssh/crypto.h \
    $$PWD/DependLibs/libssh/curve25519.h \
    $$PWD/DependLibs/libssh/dh.h \
    $$PWD/DependLibs/libssh/ecdh.h \
    $$PWD/DependLibs/libssh/ed25519.h \
    $$PWD/DependLibs/libssh/fe25519.h \
    $$PWD/DependLibs/libssh/ge25519.h \
    $$PWD/DependLibs/libssh/gssapi.h \
    $$PWD/DependLibs/libssh/kex.h \
    $$PWD/DependLibs/libssh/keys.h \
    $$PWD/DependLibs/libssh/knownhosts.h \
    $$PWD/DependLibs/libssh/legacy.h \
    $$PWD/DependLibs/libssh/libcrypto.h \
    $$PWD/DependLibs/libssh/libgcrypt.h \
    $$PWD/DependLibs/libssh/libssh.h \
    $$PWD/DependLibs/libssh/libssh_config.h \
    $$PWD/DependLibs/libssh/libssh_config_android.h \
    $$PWD/DependLibs/libssh/libssh_config_linux.h \
    $$PWD/DependLibs/libssh/libssh_config_windows.h \
    $$PWD/DependLibs/libssh/libssh_priv.h \
    $$PWD/DependLibs/libssh/libssh_string.h \
    $$PWD/DependLibs/libssh/libsshpp.hpp \
    $$PWD/DependLibs/libssh/messages.h \
    $$PWD/DependLibs/libssh/misc.h \
    $$PWD/DependLibs/libssh/options.h \
    $$PWD/DependLibs/libssh/packet.h \
    $$PWD/DependLibs/libssh/pcap.h \
    $$PWD/DependLibs/libssh/pki.h \
    $$PWD/DependLibs/libssh/pki_priv.h \
    $$PWD/DependLibs/libssh/poll_ssh.h \
    $$PWD/DependLibs/libssh/sc25519.h \
    $$PWD/DependLibs/libssh/scp.h \
    $$PWD/DependLibs/libssh/server.h \
    $$PWD/DependLibs/libssh/session.h \
    $$PWD/DependLibs/libssh/sftp.h \
    $$PWD/DependLibs/libssh/socket.h \
    $$PWD/DependLibs/libssh/ssh1.h \
    $$PWD/DependLibs/libssh/ssh2.h \
    $$PWD/DependLibs/libssh/threads.h \
    $$PWD/DependLibs/libssh/wrapper.h \
    $$PWD/DependLibs/libssh/poll_ssh.h

SOURCES += 	$$PWD/DependLibs/libssh/agent.c \
    $$PWD/DependLibs/libssh/auth.c \
    $$PWD/DependLibs/libssh/auth1.c \
    $$PWD/DependLibs/libssh/base64.c \
    $$PWD/DependLibs/libssh/bignum.c \
    $$PWD/DependLibs/libssh/bind.c \
    $$PWD/DependLibs/libssh/buffer.c \
    $$PWD/DependLibs/libssh/callbacks.c \
    $$PWD/DependLibs/libssh/channels.c \
    $$PWD/DependLibs/libssh/channels1.c \
    $$PWD/DependLibs/libssh/client.c \
    $$PWD/DependLibs/libssh/config.c \
    $$PWD/DependLibs/libssh/connect.c \
    $$PWD/DependLibs/libssh/crc32.c \
    $$PWD/DependLibs/libssh/curve25519.c \
    $$PWD/DependLibs/libssh/dh.c \
    $$PWD/DependLibs/libssh/ecdh.c \
    $$PWD/DependLibs/libssh/error.c \
    $$PWD/DependLibs/libssh/external/bcrypt_pbkdf.c \
    $$PWD/DependLibs/libssh/external/blowfish.c \
    $$PWD/DependLibs/libssh/external/curve25519_ref.c \
    $$PWD/DependLibs/libssh/external/ed25519.c \
    $$PWD/DependLibs/libssh/external/fe25519.c \
    $$PWD/DependLibs/libssh/external/ge25519.c \
    $$PWD/DependLibs/libssh/external/sc25519.c \
    $$PWD/DependLibs/libssh/gcrypt_missing.c \
    $$PWD/DependLibs/libssh/getpass.c \
    $$PWD/DependLibs/libssh/gssapi.c \
    $$PWD/DependLibs/libssh/gzip.c \
    $$PWD/DependLibs/libssh/init.c \
    $$PWD/DependLibs/libssh/kex.c \
    $$PWD/DependLibs/libssh/kex1.c \
    $$PWD/DependLibs/libssh/known_hosts.c \
    $$PWD/DependLibs/libssh/legacy.c \
    $$PWD/DependLibs/libssh/libcrypto.c \
    $$PWD/DependLibs/libssh/libgcrypt.c \
    $$PWD/DependLibs/libssh/libssh_string.c \
    $$PWD/DependLibs/libssh/log.c \
    $$PWD/DependLibs/libssh/match.c \
    $$PWD/DependLibs/libssh/messages.c \
    $$PWD/DependLibs/libssh/misc.c \
    $$PWD/DependLibs/libssh/options.c \
    $$PWD/DependLibs/libssh/packet.c \
    $$PWD/DependLibs/libssh/packet1.c \
    $$PWD/DependLibs/libssh/packet_cb.c \
    $$PWD/DependLibs/libssh/packet_crypt.c \
    $$PWD/DependLibs/libssh/pcap.c \
    $$PWD/DependLibs/libssh/pki.c \
    $$PWD/DependLibs/libssh/pki_container_openssh.c \
    $$PWD/DependLibs/libssh/pki_crypto.c \
    $$PWD/DependLibs/libssh/pki_ed25519.c \
    $$PWD/DependLibs/libssh/pki_gcrypt.c \
    $$PWD/DependLibs/libssh/scp.c \
    $$PWD/DependLibs/libssh/server.c \
    $$PWD/DependLibs/libssh/session.c \
    $$PWD/DependLibs/libssh/sftp.c \
    $$PWD/DependLibs/libssh/sftpserver.c \
    $$PWD/DependLibs/libssh/socket.c \
    $$PWD/DependLibs/libssh/threads.c \
    $$PWD/DependLibs/libssh/threads/pthread.c \
    $$PWD/DependLibs/libssh/wrapper.c \
    $$PWD/DependLibs/libssh/poll_ssh.c

