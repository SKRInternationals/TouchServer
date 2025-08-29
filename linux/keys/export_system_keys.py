# this code will export all keys and their id from
# /usr/include/linux/input-event-codes.h << this file
# and will write them into `system_keys.py` as dictionary
# systemKeys={systemKey:val}

import re

codes = {}
firstLine = True
with open("./system_keys.py","w") as save_f:
  save_f.write("systemKeys={")
  with open("/usr/include/linux/input-event-codes.h") as f:
      for line in f:
          match = re.match(r"#define\s+(KEY_\w+)\s+(\S+)", line)
          if match:
              name, value = match.groups()
              print(f"name:{name}, val: {value}")
              codes[name] = value
              nextItem = f'"{name}":"{value}"'
              if firstLine:
                firstLine=False
              else:
                nextItem = ", " + nextItem
              save_f.write(nextItem)
  save_f.write("}")


print(codes)

