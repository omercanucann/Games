extends CanvasLayer

@onready var finish_panel: Panel = $FinishPanel
@onready var finish_label: Label = $FinishPanel/FinishLabel
@onready var restart_button: Button = $FinishPanel/RestartButton
@onready var quit_button: Button = $FinishPanel/QuitButton
@onready var timer_label: Label = $TimerLabel

@onready var fuel_gauge: TextureRect = $FuelGauge
@onready var needle: Sprite2D = $FuelGauge/Needle

var min_angle := deg_to_rad(-270)
var max_angle := deg_to_rad(10)
var current_fuel := 100.0

func _ready():
	finish_panel.visible = false
	timer_label.text = "00.00"
	
	finish_panel.anchor_left = 0.5
	finish_panel.anchor_right = 0.5
	finish_panel.anchor_top = 0.5
	finish_panel.anchor_bottom = 0.5


func update_timer(time_passed: float):
	var seconds = floor(time_passed)
	var ms = int((time_passed - seconds) * 100)
	timer_label.text = "%02d.%02d" % [seconds, ms]


func show_finish_screen(time_passed: float):
	finish_panel.visible = true
	
	var seconds = floor(time_passed)
	var ms = int((time_passed - seconds) * 100)
	finish_label.text = "RACE FINISH!\nTime: %02d.%02d" % [seconds, ms]


func update_fuel(fuel: float):
	current_fuel = clamp(fuel, 0, 100)

	var t = current_fuel / 100.0
	var angle = lerp(min_angle, max_angle, t)
	needle.rotation = angle


func _on_restart_button_pressed():
	get_tree().paused = false
	get_tree().reload_current_scene()

func _on_quit_button_pressed():
	get_tree().quit()
