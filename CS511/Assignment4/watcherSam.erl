-module(watcher).
-export([start/1, createSensor/3]).

start(NumOfSensor) ->
	if
		NumOfSensor == 0 ->
			io:format("Please enter a number greater than 0.~n");
		true ->
			createSensor(NumOfSensor, [], 0)
	end.

createSensor(NumOfSensor, SensorList, SensorId) ->
	if
		length(SensorList) == 10 ->
			io:format("Watching:~n"),
			[io:format("Id: ~p, Pid: ~p~n", [Id, Pid]) || {Id, Pid} <- SensorList],
			if NumOfSensor /= 0 -> 
				spawn(watcher, createSensor, [NumOfSensor, [], SensorId]),
				watch(SensorList);
			true ->
				watch(SensorList)
			end;
		NumOfSensor == 0 ->
			io:format("Watching~n"),
			[io:format("Id: ~p, Pid: ~p~n", [Id, Pid]) || {Id, Pid} <- SensorList],
			watch(SensorList);
		true ->
			{SensorPid, _} = spawn_monitor(sensor, start, [self(), SensorId]),
			createSensor(NumOfSensor - 1, lists:merge(SensorList, [{SensorId, SensorPid}]), SensorId + 1)
	end.

restartASensor(SensorList, SensorId) ->
	{SensorPid, _} = spawn_monitor(sensor, start, [self(), SensorId]),
	io:format("    Restarted sensor: ~p, new Pid: ~p~n", [SensorId, SensorPid]),
	NewList = lists:merge(SensorList, [{SensorId, SensorPid}]),
	watch(NewList).

watch(SensorList) ->
	receive
		{die, {From, FromId}, err} ->
			io:format("Sensor ~p died~n", [FromId]),
			restartASensor(lists:delete({FromId, From}, SensorList), FromId);
		{Measurement, {From, FromId}, Ref} ->
			io:format("MSG: ~2p, From sensor ~4p~n", [Measurement, FromId]),
			From ! {ok, Ref},
			watch(SensorList)
	end.
