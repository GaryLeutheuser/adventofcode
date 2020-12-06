from passport import Passport

# Get the raw passport information.
raw_input = ""
with open("input.txt", "r") as input_file:
    raw_input = input_file.read()

# Split on double newline.
raw_passports = raw_input.split('\n\n')

# Attempt to parse the first (testing).
passports = [Passport.parse(raw_passport, True) for raw_passport in raw_passports]

valid_count = 0
for passport in passports:
    # Check every field except CID.
    if passport.byr == "":
        continue
    if passport.iyr == "":
        continue
    if passport.eyr == "":
        continue
    if passport.hgt == "":
        continue
    if passport.hcl == "":
        continue
    if passport.ecl == "":
        continue
    if passport.pid == "":
        continue
    valid_count += 1

print(valid_count)
