extends Node2D

@onready var finish_line = $FinishLine
@onready var game_ui = $GameUI
@onready var motobike = $Motobike
@onready var game_over_screen = preload("res://scenes/game_over_screen.tscn").instantiate()

var timer_running: bool = false
var current_time: float = 0.0


func _ready():
	add_child(game_over_screen)
	if finish_line and game_ui:
		finish_line.race_finished.connect(_on_race_finished)
		print("Signal connected successfully!")
	else:
		print("ERROR: FinishLine or GameUI not found!")
	motobike.game_ui = game_ui
	timer_running = true
	current_time = 0.0
	
func _process(delta):
	if timer_running:
		current_time += delta
	
	game_ui.update_timer(current_time)

func _on_race_finished():
	timer_running = false
	game_ui.show_finish_screen(current_time)
