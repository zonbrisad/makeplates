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

DblParam4=5.5

DblParam5=4.3

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

IntList = { -255, -30, 0, 1, 2, 3, 4, 10, 42, 120, 4096, 12000 }

DblList = { -80.4, -1.3, 0.0, 1.45, 5.4, 42.3, 141.94 }

InvalidList = 44

-- Boolean tests
-- -----------------------------------------------------------------

BoolParam1=O

BoolParam2=Off



-- Table tests
-- -----------------------------------------------------------------
TableParam = { a =  12,  
               b = -12.3, 
               c="  Table string", 
               d=  {9,8,7,6,5,4,3,2,1}
}

TableParamList = { { a =  1, b = -12.1, c="Table string 1", d=  {9,8,7,6,5,4,3,2,1} }, 
                   { a =  2, b = -12.2, c="Table string 2", d=  {8,7,6,5,4,3,2,1} }, 
                   { a =  3, b = -12.3, c="Table string 3", d=  {7,6,5,4,3,2,1} }, 
                   { a =  4, b = -12.4, c="Table string 4", d=  {6,5,4,3,2,1} }, 
                   { a =  5, b = -12.5, c="Table string 5", d=  {5,4,3,2,1} }, 
}

-- Function tests
-- -----------------------------------------------------------------
function MyFunction()
  print("My function is working correct")
end

function FunIntArg(val)
  print("Integer Argument test "..val)
end

function FunDblArg(val)
  print("Double Argument test "..val)
end

function FunStrArg(val)
  print("String Argument test "..val)
end

function FunIntListArg(val)
  print("Integer Argument test "..val)
end

function FunDblListArg(val)
  print("Integer Argument test "..val)
end

function FunReturnTest() 
  return -423
end


-- Other tests
-- -----------------------------------------------------------------


-- The following is a test of paramter that is missing ( do not uncomment )
--MissingParam=20
