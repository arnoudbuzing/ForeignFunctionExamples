VerificationTest[
    square = ForeignFunctionLoad["./test.dylib", "square", {"Real64"} -> "Real64"]
    ,
    _ForeignFunction
    ,
    TestID -> "ForeignFunctionTests-1"
    ,
    SameTest -> MatchQ
]

VerificationTest[
    square[2.0]
    ,
    4.0
    ,
    TestID -> "ForeignFunctionTests-2"
    ,
    SameTest -> SameQ
]

VerificationTest[
    distance = ForeignFunctionLoad["./test.dylib", "distance", {"Real64", "Real64"} -> "Real64"]
    ,
    _ForeignFunction
    ,
    TestID -> "ForeignFunctionTests-3"
    ,
    SameTest -> MatchQ
]

VerificationTest[
    distance[1.0, 2.0]
    ,
    1.0
    ,
    TestID -> "ForeignFunctionTests-4"
    ,
    SameTest -> SameQ
]

VerificationTest[
    ForeignFunctionUnload[square]
    ,
    Null
    ,
    TestID -> "ForeignFunctionTests-5"
    ,
    SameTest -> SameQ
]

VerificationTest[
    ForeignFunctionUnload[distance]
    ,
    Null
    ,
    TestID -> "ForeignFunctionTests-6"
    ,
    SameTest -> SameQ
]
 