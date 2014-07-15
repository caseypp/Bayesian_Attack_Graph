#!/usr/bin/python
import json
f=file("piz.json")
s=json.load(f)
print s
print s.keys()
print s["name"]
print s["description"]
f.close
