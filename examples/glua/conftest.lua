--[


--]

print("This is a simple test configuration file for luaconf")
print("------------------------------------------------------------")


-- Integer tests
-- -----------------------------------------------------------------

-- A correct integer parameter
IntParam1=42

-- A correct integer parameter
IntParam2=2*IntParam1

IntParam3=IntConst

-- A integer parameter with wrong type of value
IntParamInvalid1="not a integer value"

-- A integer parameter with value below range
IntParamInvalid2=-10

-- A integer parameter with value above range
IntParamInvalid3=110

-- A integer parameter with floating point value
IntParamInvalid4=12.123

IntParam4=42

IntParam5=-32


-- Double tests
-- -----------------------------------------------------------------

-- A correct double parameter
DblParam1=4.2

-- A correct double parameter
DblParam2=3*DblParam1

DblParam3=DblConst

-- A double parameter with wrong type of value
DblParamInvalid1="not a double value"

-- A double parameter with value below range
DblParamInvalid2=-10.1

-- A double parameter with value above range
DblParamInvalid3=110.2


-- String tests
-- -----------------------------------------------------------------

-- A correct string parameter

StrParam1="Liftarens"

-- A correct string parameter
StrParam2=StrParam1.." guide till galaxen "..IntParam1

StrParam3=StrConst

StrParamInvalid1=4.2


-- Boolean tests
-- -----------------------------------------------------------------

BoolParamTrue="All true  "..YES.." "..Yes.." "..yes.." "..TRUE.." "..True.." "..ON.." "..On.." "..on
BoolParamFalse="All false "..NO.." "..No.." "..no.." "..FALSE.." "..False.." "..OFF.." "..Off.." "..off

-- List tests
-- -----------------------------------------------------------------

IntList={ -255, -30, 0, 1, 2, 3, 4, 10, 42, 120, 4096, 12000 }

DblList={ -80.4, -1.3, 0.0, 1.45, 5.4, 42.3, 141.94 }

InvalidList=44

-- Boolean tests
-- -----------------------------------------------------------------

BoolParam1=O

BoolParam2=Off


-- Other tests
-- -----------------------------------------------------------------


-- The following is a test of paramter that is missing ( do not uncomment )
--MissingParam=20
