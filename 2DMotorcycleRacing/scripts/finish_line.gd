extends Area2D

signal race_finished

@export var trigger_delay: float = 1

var taxi_inside: bool = false
var trigger_timer: float = 0.0

func _ready():
	body_entered.connect(_on_body_entered)
	body_exited.connect(_on_body_exited)

func _process(delta: float):
	if taxi_inside:
		trigger_timer += delta
		if trigger_timer >= trigger_delay:
			_trigger_finish()

func _on_body_entered(body: Node2D):
	if body.name == "Motobike":
		print("The taxi has entered the finish line!")
		taxi_inside = true
		trigger_timer = 0.0

func _on_body_exited(body: Node2D):
	if body.name == "Motobike":
		taxi_inside = false
		trigger_timer = 0.0

func _trigger_finish():
	print("The finish line has been completely crossed!")
	race_finished.emit()
	monitoring = false
	taxi_inside = false
