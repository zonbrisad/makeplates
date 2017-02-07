
print("This is a simple test configuration file for luaconf")
print("------------------------------------------------------------")


-- Integer tests
-- -----------------------------------------------------------------

-- A correct integer parameter
IntParam1=42

-- A integer parameter with wrong type of value
IntParamInvalid1="not a integer value"

-- A integer parameter with value below range
IntParamInvalid2=-10

-- A integer parameter with value above range
IntParamInvalid3=110


-- Double tests
-- -----------------------------------------------------------------

-- A correct double parameter
DblParam1=4.2

-- A double parameter with wrong type of value
DblParamInvalid1="not a double value"

-- A double parameter with value below range
DblParamInvalid2=-10.1

-- A double parameter with value above range
DblParamInvalid3=110.2


-- String tests
-- -----------------------------------------------------------------

-- A correct string parameter
StrParam1="Liftaren"

StrParamInvalid1=4.2


-- List tests
-- -----------------------------------------------------------------

IntList={ -255, -30, 0, 1, 2, 3, 4, 10, 42, 120, 4096, 12000 }

DblList={ -80.4, -1.3, 0.0, 1.45, 5.4, 42.3, 141,94 }


-- Boolean tests
-- -----------------------------------------------------------------
--BoolParam=O


-- Other tests
-- -----------------------------------------------------------------


-- The following is a test of paramter that is missing ( do not uncomment )
--MissingParam=20
