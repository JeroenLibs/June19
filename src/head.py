from glob import glob

out="#pragma once\n"

for k in glob("*.hpp"):
    if k!="june19.hpp" and k!="june19_jcr6.hpp":
        print(k)
        out += "#include \"%s\"\n"%k

text_file = open("june19.hpp", "w")
text_file.write(out)
text_file.close()    

# Hey I'm lazy and this Python script saves me tons of work, mind you?
    