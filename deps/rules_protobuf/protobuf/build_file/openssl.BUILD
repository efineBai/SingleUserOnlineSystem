config_setting(
    name = "darwin",
    values = {
        "cpu": "darwin_x86_64",
    },
)

cc_library(
    name = "crypto",
    hdrs = ["include/openssl/aes.h"]+
          ["include/openssl/bn.h"]+
          ["include/openssl/comp.h"]+
          ["include/openssl/dh.h"]+
          ["include/openssl/ec.h"]+
          ["include/openssl/hmac.h"]+
          ["include/openssl/md5.h"]+
          ["include/openssl/opensslconf.h"]+
          ["include/openssl/pkcs7.h"]+
          ["include/openssl/rsa.h"]+
          ["include/openssl/ssl.h"]+
          ["include/openssl/tls1.h"]+
          ["include/openssl/x509.h"]+
          ["include/openssl/asn1.h"]+
          ["include/openssl/buffer.h"]+
          ["include/openssl/conf.h"]+
          ["include/openssl/dsa.h"]+
          ["include/openssl/ecdh.h"]+
          ["include/openssl/idea.h"]+
          ["include/openssl/mdc2.h"]+
          ["include/openssl/opensslv.h"]+
          ["include/openssl/pqueue.h"]+
          ["include/openssl/safestack.h"]+
          ["include/openssl/ssl2.h"]+
          ["include/openssl/ts.h"]+
          ["include/openssl/x509_vfy.h"]+
          ["include/openssl/asn1_mac.h"]+
          ["include/openssl/camellia.h"]+
          ["include/openssl/conf_api.h"]+
          ["include/openssl/dso.h"]+
          ["include/openssl/ecdsa.h"]+
          ["include/openssl/krb5_asn.h"]+
          ["include/openssl/modes.h"]+
          ["include/openssl/ossl_typ.h"]+
          ["include/openssl/rand.h"]+
          ["include/openssl/seed.h"]+
          ["include/openssl/ssl23.h"]+
          ["include/openssl/txt_db.h"]+
          ["include/openssl/x509v3.h"]+
          ["include/openssl/asn1t.h"]+
          ["include/openssl/cast.h"]+
          ["include/openssl/crypto.h"]+
          ["include/openssl/dtls1.h"]+
          ["include/openssl/engine.h"]+
          ["include/openssl/kssl.h"]+
          ["include/openssl/obj_mac.h"]+
          ["include/openssl/pem.h"]+
          ["include/openssl/rc2.h"]+
          ["include/openssl/sha.h"]+
          ["include/openssl/ssl3.h"]+
          ["include/openssl/ui.h"]+
          ["include/openssl/bio.h"]+
          ["include/openssl/cmac.h"]+
          ["include/openssl/des.h"]+
          ["include/openssl/e_os2.h"]+
          ["include/openssl/err.h"]+
          ["include/openssl/lhash.h"]+
          ["include/openssl/objects.h"]+
          ["include/openssl/pem2.h"]+
          ["include/openssl/rc4.h"]+
          ["include/openssl/srp.h"]+
          ["include/openssl/stack.h"]+
          ["include/openssl/ui_compat.h"]+
          ["include/openssl/blowfish.h"]+
          ["include/openssl/cms.h"]+
          ["include/openssl/des_old.h"]+
          ["include/openssl/ebcdic.h"]+
          ["include/openssl/evp.h"]+
          ["include/openssl/md4.h"]+
          ["include/openssl/ocsp.h"]+
          ["include/openssl/pkcs12.h"]+
          ["include/openssl/ripemd.h"]+
          ["include/openssl/srtp.h"]+
          ["include/openssl/symhacks.h"]+
          ["include/openssl/whrlpool.h"],
    srcs = ["libcrypto.a" ],
    includes = ["include"],
   
    linkopts = select({
        ":darwin": [],
        "//conditions:default": ["-lpthread", "-ldl"],
    }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ssl",
    deps = [":crypto"],
    hdrs =    ["include/openssl/aes.h"]+
              ["include/openssl/bn.h"]+
              ["include/openssl/comp.h"]+
              ["include/openssl/dh.h"]+
              ["include/openssl/ec.h"]+
              ["include/openssl/hmac.h"]+
              ["include/openssl/md5.h"]+
              ["include/openssl/opensslconf.h"]+
              ["include/openssl/pkcs7.h"]+
              ["include/openssl/rsa.h"]+
              ["include/openssl/ssl.h"]+
              ["include/openssl/tls1.h"]+
              ["include/openssl/x509.h"]+
              ["include/openssl/asn1.h"]+
              ["include/openssl/buffer.h"]+
              ["include/openssl/conf.h"]+
              ["include/openssl/dsa.h"]+
              ["include/openssl/ecdh.h"]+
              ["include/openssl/idea.h"]+
              ["include/openssl/mdc2.h"]+
              ["include/openssl/opensslv.h"]+
              ["include/openssl/pqueue.h"]+
              ["include/openssl/safestack.h"]+
              ["include/openssl/ssl2.h"]+
              ["include/openssl/ts.h"]+
              ["include/openssl/x509_vfy.h"]+
              ["include/openssl/asn1_mac.h"]+
              ["include/openssl/camellia.h"]+
              ["include/openssl/conf_api.h"]+
              ["include/openssl/dso.h"]+
              ["include/openssl/ecdsa.h"]+
              ["include/openssl/krb5_asn.h"]+
              ["include/openssl/modes.h"]+
              ["include/openssl/ossl_typ.h"]+
              ["include/openssl/rand.h"]+
              ["include/openssl/seed.h"]+
              ["include/openssl/ssl23.h"]+
              ["include/openssl/txt_db.h"]+
              ["include/openssl/x509v3.h"]+
              ["include/openssl/asn1t.h"]+
              ["include/openssl/cast.h"]+
              ["include/openssl/crypto.h"]+
              ["include/openssl/dtls1.h"]+
              ["include/openssl/engine.h"]+
              ["include/openssl/kssl.h"]+
              ["include/openssl/obj_mac.h"]+
              ["include/openssl/pem.h"]+
              ["include/openssl/rc2.h"]+
              ["include/openssl/sha.h"]+
              ["include/openssl/ssl3.h"]+
              ["include/openssl/ui.h"]+
              ["include/openssl/bio.h"]+
              ["include/openssl/cmac.h"]+
              ["include/openssl/des.h"]+
              ["include/openssl/e_os2.h"]+
              ["include/openssl/err.h"]+
              ["include/openssl/lhash.h"]+
              ["include/openssl/objects.h"]+
              ["include/openssl/pem2.h"]+
              ["include/openssl/rc4.h"]+
              ["include/openssl/srp.h"]+
              ["include/openssl/stack.h"]+
              ["include/openssl/ui_compat.h"]+
              ["include/openssl/blowfish.h"]+
              ["include/openssl/cms.h"]+
              ["include/openssl/des_old.h"]+
              ["include/openssl/ebcdic.h"]+
              ["include/openssl/evp.h"]+
              ["include/openssl/md4.h"]+
              ["include/openssl/ocsp.h"]+
              ["include/openssl/pkcs12.h"]+
              ["include/openssl/ripemd.h"]+
              ["include/openssl/srtp.h"]+
              ["include/openssl/symhacks.h"]+
              ["include/openssl/whrlpool.h"],
    srcs = ["libssl.a"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

genrule(
    name = "openssl-build",
    srcs = glob(["**/*"], exclude=["bazel-*"]),
    outs = [
        "libcrypto.a",
        "libssl.a",
         "include/openssl/aes.h",
         "include/openssl/bn.h",
         "include/openssl/comp.h",
         "include/openssl/dh.h",
         "include/openssl/ec.h",
         "include/openssl/hmac.h",
         "include/openssl/md5.h",
         "include/openssl/opensslconf.h",
         "include/openssl/pkcs7.h",
         "include/openssl/rsa.h",
         "include/openssl/ssl.h",
         "include/openssl/tls1.h",
         "include/openssl/x509.h",
         "include/openssl/asn1.h",
         "include/openssl/buffer.h",
         "include/openssl/conf.h",
         "include/openssl/dsa.h",
         "include/openssl/ecdh.h",
         "include/openssl/idea.h",
         "include/openssl/mdc2.h",
         "include/openssl/opensslv.h",
         "include/openssl/pqueue.h",
         "include/openssl/safestack.h",
         "include/openssl/ssl2.h",
         "include/openssl/ts.h",
         "include/openssl/x509_vfy.h",
         "include/openssl/asn1_mac.h",
         "include/openssl/camellia.h",
         "include/openssl/conf_api.h",
         "include/openssl/dso.h",
         "include/openssl/ecdsa.h",
         "include/openssl/krb5_asn.h",
         "include/openssl/modes.h",
         "include/openssl/ossl_typ.h",
         "include/openssl/rand.h",
         "include/openssl/seed.h",
         "include/openssl/ssl23.h",
         "include/openssl/txt_db.h",
         "include/openssl/x509v3.h",
         "include/openssl/asn1t.h",
         "include/openssl/cast.h",
         "include/openssl/crypto.h",
         "include/openssl/dtls1.h",
         "include/openssl/engine.h",
         "include/openssl/kssl.h",
         "include/openssl/obj_mac.h",
         "include/openssl/pem.h",
         "include/openssl/rc2.h",
         "include/openssl/sha.h",
         "include/openssl/ssl3.h",
         "include/openssl/ui.h",
         "include/openssl/bio.h",
         "include/openssl/cmac.h",
         "include/openssl/des.h",
         "include/openssl/e_os2.h",
         "include/openssl/err.h",
         "include/openssl/lhash.h",
         "include/openssl/objects.h",
         "include/openssl/pem2.h",
         "include/openssl/rc4.h",
         "include/openssl/srp.h",
         "include/openssl/stack.h",
         "include/openssl/ui_compat.h",
         "include/openssl/blowfish.h",
         "include/openssl/cms.h",
         "include/openssl/des_old.h",
         "include/openssl/ebcdic.h",
         "include/openssl/evp.h",
         "include/openssl/md4.h",
         "include/openssl/ocsp.h",
         "include/openssl/pkcs12.h",
         "include/openssl/ripemd.h",
         "include/openssl/srtp.h",
         "include/openssl/symhacks.h",
         "include/openssl/whrlpool.h",
    ],

    cmd = """
        OPENSSL_ROOT=$$(dirname $(location config))
        pushd $$OPENSSL_ROOT 
            ./Configure darwin64-x86_64-cc
            make
        popd
        cp $$OPENSSL_ROOT/libcrypto.a $(location libcrypto.a)
        cp $$OPENSSL_ROOT/libssl.a $(location libssl.a)
        cp $$OPENSSL_ROOT/include/openssl/aes.h  $(location include/openssl/aes.h)
        cp $$OPENSSL_ROOT/include/openssl/bn.h   $(location include/openssl/bn.h)
        cp $$OPENSSL_ROOT/include/openssl/comp.h     $(location include/openssl/comp.h)
        cp $$OPENSSL_ROOT/include/openssl/dh.h   $(location include/openssl/dh.h)
        cp $$OPENSSL_ROOT/include/openssl/ec.h   $(location include/openssl/ec.h)
        cp $$OPENSSL_ROOT/include/openssl/hmac.h     $(location include/openssl/hmac.h)
        cp $$OPENSSL_ROOT/include/openssl/md5.h  $(location include/openssl/md5.h)
        cp $$OPENSSL_ROOT/include/openssl/opensslconf.h  $(location include/openssl/opensslconf.h)
        cp $$OPENSSL_ROOT/include/openssl/pkcs7.h    $(location include/openssl/pkcs7.h)
        cp $$OPENSSL_ROOT/include/openssl/rsa.h  $(location include/openssl/rsa.h)
        cp $$OPENSSL_ROOT/include/openssl/ssl.h  $(location include/openssl/ssl.h)
        cp $$OPENSSL_ROOT/include/openssl/tls1.h     $(location include/openssl/tls1.h)
        cp $$OPENSSL_ROOT/include/openssl/x509.h     $(location include/openssl/x509.h)
        cp $$OPENSSL_ROOT/include/openssl/asn1.h     $(location include/openssl/asn1.h)
        cp $$OPENSSL_ROOT/include/openssl/buffer.h   $(location include/openssl/buffer.h)
        cp $$OPENSSL_ROOT/include/openssl/conf.h     $(location include/openssl/conf.h)
        cp $$OPENSSL_ROOT/include/openssl/dsa.h  $(location include/openssl/dsa.h)
        cp $$OPENSSL_ROOT/include/openssl/ecdh.h     $(location include/openssl/ecdh.h)
        cp $$OPENSSL_ROOT/include/openssl/idea.h     $(location include/openssl/idea.h)
        cp $$OPENSSL_ROOT/include/openssl/mdc2.h     $(location include/openssl/mdc2.h)
        cp $$OPENSSL_ROOT/include/openssl/opensslv.h     $(location include/openssl/opensslv.h)
        cp $$OPENSSL_ROOT/include/openssl/pqueue.h   $(location include/openssl/pqueue.h)
        cp $$OPENSSL_ROOT/include/openssl/safestack.h    $(location include/openssl/safestack.h)
        cp $$OPENSSL_ROOT/include/openssl/ssl2.h     $(location include/openssl/ssl2.h)
        cp $$OPENSSL_ROOT/include/openssl/ts.h   $(location include/openssl/ts.h)
        cp $$OPENSSL_ROOT/include/openssl/x509_vfy.h     $(location include/openssl/x509_vfy.h)
        cp $$OPENSSL_ROOT/include/openssl/asn1_mac.h     $(location include/openssl/asn1_mac.h)
        cp $$OPENSSL_ROOT/include/openssl/camellia.h     $(location include/openssl/camellia.h)
        cp $$OPENSSL_ROOT/include/openssl/conf_api.h     $(location include/openssl/conf_api.h)
        cp $$OPENSSL_ROOT/include/openssl/dso.h  $(location include/openssl/dso.h)
        cp $$OPENSSL_ROOT/include/openssl/ecdsa.h    $(location include/openssl/ecdsa.h)
        cp $$OPENSSL_ROOT/include/openssl/krb5_asn.h     $(location include/openssl/krb5_asn.h)
        cp $$OPENSSL_ROOT/include/openssl/modes.h    $(location include/openssl/modes.h)
        cp $$OPENSSL_ROOT/include/openssl/ossl_typ.h     $(location include/openssl/ossl_typ.h)
        cp $$OPENSSL_ROOT/include/openssl/rand.h     $(location include/openssl/rand.h)
        cp $$OPENSSL_ROOT/include/openssl/seed.h     $(location include/openssl/seed.h)
        cp $$OPENSSL_ROOT/include/openssl/ssl23.h    $(location include/openssl/ssl23.h)
        cp $$OPENSSL_ROOT/include/openssl/txt_db.h   $(location include/openssl/txt_db.h)
        cp $$OPENSSL_ROOT/include/openssl/x509v3.h   $(location include/openssl/x509v3.h)
        cp $$OPENSSL_ROOT/include/openssl/asn1t.h    $(location include/openssl/asn1t.h)
        cp $$OPENSSL_ROOT/include/openssl/cast.h     $(location include/openssl/cast.h)
        cp $$OPENSSL_ROOT/include/openssl/crypto.h   $(location include/openssl/crypto.h)
        cp $$OPENSSL_ROOT/include/openssl/dtls1.h    $(location include/openssl/dtls1.h)
        cp $$OPENSSL_ROOT/include/openssl/engine.h   $(location include/openssl/engine.h)
        cp $$OPENSSL_ROOT/include/openssl/kssl.h     $(location include/openssl/kssl.h)
        cp $$OPENSSL_ROOT/include/openssl/obj_mac.h  $(location include/openssl/obj_mac.h)
        cp $$OPENSSL_ROOT/include/openssl/pem.h  $(location include/openssl/pem.h)
        cp $$OPENSSL_ROOT/include/openssl/rc2.h  $(location include/openssl/rc2.h)
        cp $$OPENSSL_ROOT/include/openssl/sha.h  $(location include/openssl/sha.h)
        cp $$OPENSSL_ROOT/include/openssl/ssl3.h     $(location include/openssl/ssl3.h)
        cp $$OPENSSL_ROOT/include/openssl/ui.h   $(location include/openssl/ui.h)
        cp $$OPENSSL_ROOT/include/openssl/bio.h  $(location include/openssl/bio.h)
        cp $$OPENSSL_ROOT/include/openssl/cmac.h     $(location include/openssl/cmac.h)
        cp $$OPENSSL_ROOT/include/openssl/des.h  $(location include/openssl/des.h)
        cp $$OPENSSL_ROOT/include/openssl/e_os2.h    $(location include/openssl/e_os2.h)
        cp $$OPENSSL_ROOT/include/openssl/err.h  $(location include/openssl/err.h)
        cp $$OPENSSL_ROOT/include/openssl/lhash.h    $(location include/openssl/lhash.h)
        cp $$OPENSSL_ROOT/include/openssl/objects.h  $(location include/openssl/objects.h)
        cp $$OPENSSL_ROOT/include/openssl/pem2.h     $(location include/openssl/pem2.h)
        cp $$OPENSSL_ROOT/include/openssl/rc4.h  $(location include/openssl/rc4.h)
        cp $$OPENSSL_ROOT/include/openssl/srp.h  $(location include/openssl/srp.h)
        cp $$OPENSSL_ROOT/include/openssl/stack.h    $(location include/openssl/stack.h)
        cp $$OPENSSL_ROOT/include/openssl/ui_compat.h    $(location include/openssl/ui_compat.h)
        cp $$OPENSSL_ROOT/include/openssl/blowfish.h     $(location include/openssl/blowfish.h)
        cp $$OPENSSL_ROOT/include/openssl/cms.h  $(location include/openssl/cms.h)
        cp $$OPENSSL_ROOT/include/openssl/des_old.h  $(location include/openssl/des_old.h)
        cp $$OPENSSL_ROOT/include/openssl/ebcdic.h   $(location include/openssl/ebcdic.h)
        cp $$OPENSSL_ROOT/include/openssl/evp.h  $(location include/openssl/evp.h)
        cp $$OPENSSL_ROOT/include/openssl/md4.h  $(location include/openssl/md4.h)
        cp $$OPENSSL_ROOT/include/openssl/ocsp.h     $(location include/openssl/ocsp.h)
        cp $$OPENSSL_ROOT/include/openssl/pkcs12.h   $(location include/openssl/pkcs12.h)
        cp $$OPENSSL_ROOT/include/openssl/ripemd.h   $(location include/openssl/ripemd.h)
        cp $$OPENSSL_ROOT/include/openssl/srtp.h     $(location include/openssl/srtp.h)
        cp $$OPENSSL_ROOT/include/openssl/symhacks.h     $(location include/openssl/symhacks.h)
        cp $$OPENSSL_ROOT/include/openssl/whrlpool.h     $(location include/openssl/whrlpool.h)
    """,
)