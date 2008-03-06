#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re, urllib2

pattern = re.compile(r"^(\w{2})$")
TLDs = urllib2.urlopen("http://data.iana.org/TLD/tlds-alpha-by-domain.txt")
urlTmpl = "http://images.tvrage.com/flags/%s.gif"

for tld in TLDs.readlines():
    m = pattern.match(tld)
    if m:
        country = m.group(1).lower()
        try:
            fpin = urllib2.urlopen( urlTmpl % country )
        except:
            print "%s NOK" % country
            continue
        fpout = open( "%s.gif" % country, "wb")
        print >> fpout, fpin.read()
        fpout.close()
        print "%s OK" % country
