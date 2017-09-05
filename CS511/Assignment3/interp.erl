% John Spicer
% Michael Osorio

-module(interp).
-export([scanAndParse/1,runFile/1,runStr/1]).
-include("types.hrl").

loop(InFile,Acc) ->
    case io:request(InFile,{get_until,prompt,lexer,token,[1]}) of
        {ok,Token,_EndLine} ->
            loop(InFile,Acc ++ [Token]);
        {error,token} ->
            exit(scanning_error);
        {eof,_} ->
            Acc
    end.

scanAndParse(FileName) ->
    {ok, InFile} = file:open(FileName, [read]),
    Acc = loop(InFile,[]),
    file:close(InFile),
    {Result, AST} = parser:parse(Acc),
    case Result of 
    ok -> AST;
    _ -> io:format("Parse error~n")
    end.


-spec runFile(string()) -> valType().
runFile(FileName) ->
    valueOf(scanAndParse(FileName),env:new()).

scanAndParseString(String) ->
    {_ResultL, TKs, _L} = lexer:string(String),
    parser:parse(TKs).

-spec runStr(string()) -> valType().
runStr(String) ->
    {Result, AST} = scanAndParseString(String),
    case Result  of 
        ok -> valueOf(AST,env:new());
        _ -> io:format("Parse error~n")
    end.


-spec numVal2Num(numValType()) -> integer().
numVal2Num({num, N}) ->
    N.

-spec boolVal2Bool(boolValType()) -> boolean().
boolVal2Bool({bool, B}) ->
    B.

-spec valueOf(expType(),envType()) -> valType().
valueOf(Exp, Env) ->
    case Exp of
        {numExp, {num, _, Val}} = Exp ->
            {num, Val};
        {idExp, {id, _, Id}} = Exp ->
            env:lookup(Env, Id);
        {plusExp, LeftOpd, RightOpd} = Exp ->
            {num, (numVal2Num(valueOf(LeftOpd, Env))
                   + numVal2Num(valueOf(RightOpd, Env)))};
        {procExp, {_, _, Id}, Body} = Exp ->
            {proc, Id, Body, Env};
        {letExp, {_, _, Id}, Val, Body} = Exp ->
            NewEnv = env:add(Env, Id, valueOf(Val, Env)),
            valueOf(Body, NewEnv);
        {appExp, IdExp, ParamExp} = Exp = Exp ->
            {_, Id, Val, _} = valueOf(IdExp, Env),
            NewEnv = env:add(Env, Id, valueOf(ParamExp, Env)),
            valueOf(Val, NewEnv);
        {isZeroExp, NumExp} = Exp ->
            Val = numVal2Num(valueOf(NumExp, Env)),
            if
                Val == 0 -> complete
                    {bool, true};
                true ->
                    {bool, false}
            end
    end.
