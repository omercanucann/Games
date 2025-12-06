extends CanvasLayer

@onready var finish_panel: Panel = $FinishPanel
@onready var finish_label: Label = $FinishPanel/FinishLabel
@onready var restart_button: Button = $FinishPanel/RestartButton
@onready var quit_button: Button = $FinishPanel/QuitButton
@onready var timer_label: Label = $TimerLabel

func _ready():
	finish_panel.visible = false
	timer_label.text = "00.00"

	finish_panel.anchor_left = 0.5
	finish_panel.anchor_right = 0.5
	finish_panel.anchor_top = 0.5
	finish_panel.anchor_bottom = 0.5
	
	restart_button.pressed.connect(_on_restart_button_pressed)
	quit_button.pressed.connect(_on_quit_button_pressed)
	
func update_timer(time_passed: float):
	var seconds = floor(time_passed)
	var ms = int((time_passed - seconds) * 100)
	timer_label.text = "%02d.%02d" % [seconds, ms]

func show_finish_screen(time_passed: float):
	finish_panel.visible = true
	
	var seconds = floor(time_passed)
	var ms = int((time_passed - seconds) * 100)
	finish_label.text = "RACE FINISH!\nTime: %02d.%02d" % [seconds, ms]
	
	
func _on_quit_button_pressed() -> void:
	get_tree().paused = false
	get_tree().reload_current_scene()


func _on_restart_button_pressed() -> void:
	get_tree().quit()
