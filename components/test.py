from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)


from component_Hachage import component_Hachage
from signature_component import Signature

s = Signature()
private = "eec2b599b65b98f05093057ebcd04695f203ef42a6ae5db65f52e227d4dc8db5"
public = "a6654ccc4d731f4679db99f57e2b6288e6ca16e09010c0a06ef532b107a2cb80cd8b8b24294e22261a2e10171abc324d9785745e740b35c8096188eda171c33b"
sign = s.signMessage("abc", private)
print(sign)
print(s.validateSignature("abc", public, sign))
