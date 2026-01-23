#ifndef JOHN_OSSL_COMPAT_H
#define JOHN_OSSL_COMPAT_H
/* Force rebuild */

#include <openssl/opensslv.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#if OPENSSL_VERSION_NUMBER < 0x10100000L || defined(LIBRESSL_VERSION_NUMBER)

#define HMAC_CTX_new()          (HMAC_CTX *)calloc(1, sizeof(HMAC_CTX))
#define HMAC_CTX_free(ctx)      do { if (ctx) { HMAC_CTX_cleanup(ctx); free(ctx); } } while(0)
#define HMAC_CTX_reset(ctx)     HMAC_CTX_cleanup(ctx)

#define EVP_CIPHER_CTX_new()    (EVP_CIPHER_CTX *)calloc(1, sizeof(EVP_CIPHER_CTX))
#define EVP_CIPHER_CTX_free(ctx) do { if (ctx) { EVP_CIPHER_CTX_cleanup(ctx); free(ctx); } } while(0)
#define EVP_CIPHER_CTX_reset(ctx) EVP_CIPHER_CTX_cleanup(ctx)

#define DSA_get0_p(d) ((d)->p)
#define DSA_get0_q(d) ((d)->q)
#define DSA_get0_g(d) ((d)->g)
#define DSA_get0_pub_key(d) ((d)->pub_key)
#define DSA_get0_priv_key(d) ((d)->priv_key)

static inline int DSA_set0_pqg(DSA *d, BIGNUM *p, BIGNUM *q, BIGNUM *g) {
	if (p) d->p = p;
	if (q) d->q = q;
	if (g) d->g = g;
	return 1;
}

static inline int DSA_set0_key(DSA *d, BIGNUM *pub_key, BIGNUM *priv_key) {
	if (pub_key) d->pub_key = pub_key;
	if (priv_key) d->priv_key = priv_key;
	return 1;
}

#define DSA_new_compat()         (DSA *)calloc(1, sizeof(DSA))
#define DSA_free_compat(d)       do { if (d) { if (d->p) BN_free(d->p); if (d->q) BN_free(d->q); if (d->g) BN_free(d->g); if (d->pub_key) BN_free(d->pub_key); if (d->priv_key) BN_free(d->priv_key); free(d); } } while(0)

#else

#define DSA_new_compat() DSA_new()
#define DSA_free_compat(d) DSA_free(d)

#endif

#endif
