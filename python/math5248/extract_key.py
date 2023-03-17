import os
import sys

from Crypto.PublicKey import RSA

if __name__ == "__main__":
    if os.path.exists(sys.argv[1]) and os.path.exists(sys.argv[1] + ".pub"):
        f_private = open(sys.argv[1], "r")
        f_public = open(sys.argv[1] + ".pub", "r")

        private_key = RSA.importKey(f_private.read())
        public_key = RSA.importKey(f_public.read())

        print(
            "p: {}\nq: {}\nn: {}\ne: {}".format(
                private_key.p,
                private_key.q,
                public_key.n,
                public_key.e,
            )
        )

    else:
        print("invalid key file(s)")
