-module(sensor).
-export([start/2, senseAndReport/3]).
-author("John Spicer and Michael Osorio").
%I pledge my honor that I have abided by the Stevens Honor System.

start(WatcherPid, SensorId) ->
	Ref = make_ref(),
	senseAndReport(WatcherPid, SensorId, Ref).

senseAndReport(WatcherPid, SensorId, Ref) ->
	Measurement = rand:uniform(11),
	if Measurement == 11 ->
			WatcherPid ! {kill, {self(), SensorId}, error},
			exit(error);
		true ->
			WatcherPid ! {Measurement, {self(), SensorId}, Ref}
	end,
	receive
		{ok, Ref} ->
			Sleep_time = rand:uniform(10000),
			timer:sleep(Sleep_time),
			senseAndReport(WatcherPid, SensorId, Ref)
	end.
