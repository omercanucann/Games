extends Area2D

signal slow_down
signal speed_restore

func _ready():
	body_entered.connect(_on_body_entered)
	body_exited.connect(_on_body_exited)

func _on_body_entered(body):
	if body.name == "Motobike":
		emit_signal("slow_down")

func _on_body_exited(body):
	if body.name == "Motobike":
		emit_signal("speed_restore")
