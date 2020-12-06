import re

class Passport:
    def __init__(self):
        self.byr = "" # numeric, 4 digits
        self.iyr = "" # numeric, 4 digits
        self.eyr = "" # numeric, 4 digits
        self.hgt = "" # numeric + "cm"
        self.hcl = "" # optional "#" + hex color code (6 digit)
        self.ecl = "" # 3 alphabetic character code, or hex code
        self.pid = "" # optional "#" + numeric, length varies
        self.cid = "" # numeric, length varies

    def __str__(self):
        string = "Passport information:\n"
        string += f"\tBirth year (byr): {self.byr}\n"
        string += f"\tIssue year (iyr): {self.iyr}\n"
        string += f"\tExpiration year (eyr): {self.eyr}\n"
        string += f"\tHeight (hgt): {self.hgt}\n"
        string += f"\tHair color (hcl): {self.hcl}\n"
        string += f"\tEye color (ecl): {self.ecl}\n"
        string += f"\tPassport ID (pid): {self.pid}\n"
        string += f"\tCountry ID (cid): {self.cid}"
        return string

    @staticmethod
    def _find_field_value(raw_string, field):
        re_string = r":[^\s^\n]+"
        re_string = field + re_string
        compiled_re = re.compile(re_string)
        field = compiled_re.findall(raw_string)
        # Field not present.
        if len(field) != 1:
            return ""

        return field[0][4:]
        

    @staticmethod
    def parse(raw_string, validate):
        """
        Returns a Passport object based on the information
        in the input string.
        """        
        # Go field by field.
        passport = Passport()

        if not validate:
            # Non-validation mode.
            passport.byr = Passport._find_field_value(raw_string, "byr")
            passport.iyr = Passport._find_field_value(raw_string, "iyr")
            passport.eyr = Passport._find_field_value(raw_string, "eyr")
            passport.hgt = Passport._find_field_value(raw_string, "hgt")
            passport.hcl = Passport._find_field_value(raw_string, "hcl")
            passport.ecl = Passport._find_field_value(raw_string, "ecl")
            passport.pid = Passport._find_field_value(raw_string, "pid")
            passport.cid = Passport._find_field_value(raw_string, "cid")
            return passport

        # Validation mode.
        # byr
        byr_value = Passport._find_field_value(raw_string, "byr")
        if len(byr_value) != 4:
            byr_value = ""
        try:
            byr_value = int(byr_value)
            if byr_value < 1920 or byr_value > 2002:
                byr_value = ""
        except Exception:
            byr_value = ""
        passport.byr = byr_value

        # iyr
        iyr_value = Passport._find_field_value(raw_string, "iyr")
        if len(iyr_value) != 4:
            iyr_value = ""
        try:
            iyr_value = int(iyr_value)
            if iyr_value < 2010 or iyr_value > 2020:
                iyr_value = ""
        except Exception:
            iyr_value = ""
        passport.iyr = iyr_value
        
        # eyr
        eyr_value = Passport._find_field_value(raw_string, "eyr")
        if len(eyr_value) != 4:
            eyr_value = ""
        try:
            eyr_value = int(eyr_value)
            if eyr_value < 2020 or eyr_value > 2030:
                eyr_value = ""
        except Exception:
            eyr_value = ""
        passport.eyr = eyr_value
        
        # hgt
        hgt_value = Passport._find_field_value(raw_string, "hgt")
        height_number = hgt_value[0:-2]
        height_units = hgt_value[-2:]
        try:
            height_number = int(height_number)
            if height_units == "cm":
                if height_number < 150 or height_number > 193:
                    hgt_value = ""
            elif height_units == "in":
                if height_number < 59 or height_number > 76:
                    hgt_value = ""
            else:
                hgt_value = ""
        except Exception:
            hgt_value = ""
        passport.hgt = hgt_value
        
        # hcl
        hcl_value = Passport._find_field_value(raw_string, "hcl")
        hcl_re_string = r"#[0-9a-f]{6}"
        hcl_re = re.compile(hcl_re_string)
        instances = hcl_re.findall(hcl_value)
        if len(instances) != 1:
            hcl_value = ""
        passport.hcl = hcl_value
        
        # ecl
        ecl_value = Passport._find_field_value(raw_string, "ecl")
        eye_colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}
        if ecl_value not in eye_colors:
            ecl_value = ""
        passport.ecl = ecl_value
        
        # pid
        pid_value = Passport._find_field_value(raw_string, "pid")
        if len(pid_value) != 9:
            pid_value = ""
        try:
            int(pid_value)
        except Exception:
            pid_value = ""
        passport.pid = pid_value

        # cid is always okay
        passport.cid = Passport._find_field_value(raw_string, "cid")

        return passport
