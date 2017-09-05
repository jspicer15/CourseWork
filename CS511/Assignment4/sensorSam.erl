-module(sensor).
-export([start/2]).

start(WatcherPid, SensorId) ->
	Ref = make_ref(),
	senseAndReport(WatcherPid, SensorId, Ref).

senseAndReport(WatcherPid, SensorId, Ref) ->
	Measurement = random:uniform(11),
	if 
		Measurement == 11 ->
			WatcherPid ! {die, {self(), SensorId}, err},
			exit(err);
		true ->
			WatcherPid ! {Measurement, {self(), SensorId}, Ref}
	end,
	receive
		{ok, Ref} ->
			Sleep_time = random:uniform(10000),
			timer:sleep(Sleep_time),
			senseAndReport(WatcherPid, SensorId, Ref)
	end.
