extends CharacterBody2D

@export var max_speed: float = 600.0
@export var acceleration: float = 400.0
@export var deceleration: float = 600.0
@export var normal_speed: float = 600.0
@export var slow_speed: float = 100.0

@onready var animated_sprite: AnimatedSprite2D = $AnimatedSprite2D

var current_direction: Vector2 = Vector2.ZERO
var last_direction: Vector2 = Vector2.LEFT

var initialized_distance := false
var last_position: Vector2
var fuel: float = 100.0
var fuel_consumption_rate: float = 0.03
var game_ui

func _ready():
	last_position = global_position

func _physics_process(delta: float):
	game_ui.update_fuel(fuel)
	if not initialized_distance:
		last_position = global_position
		initialized_distance = true
		return
	var input_direction = get_input_direction()
	
	var distance = global_position.distance_to(last_position)
	fuel -= distance * fuel_consumption_rate
	fuel = clamp(fuel, 0, 100)
	last_position = global_position
	if game_ui:
		game_ui.update_fuel(fuel)
	if fuel <= 0:
		_on_fuel_empty()
		return

	
	
	if input_direction != Vector2.ZERO:
		velocity = velocity.move_toward(input_direction * max_speed, acceleration * delta)
		current_direction = input_direction
		last_direction = input_direction
		update_animation(input_direction, true)
	else:
		velocity = velocity.move_toward(Vector2.ZERO, deceleration * delta)
		update_animation(last_direction, false)
	move_and_slide()

func get_input_direction() -> Vector2:
	var direction = Vector2.ZERO
	
	if Input.is_action_pressed("ui_right"):
		direction.x += 1
	if Input.is_action_pressed("ui_left"):
		direction.x -= 1
	if Input.is_action_pressed("ui_down"):
		direction.y += 1
	if Input.is_action_pressed("ui_up"):
		direction.y -= 1

	return direction.normalized()
	
func update_animation(direction: Vector2, is_moving: bool):
	var anim_name = ""

	if abs(direction.x) > abs(direction.y):
		if direction.x > 0:
			anim_name = "move_right"
		else:
			anim_name = "move_left"
	else:
		if direction.y > 0:
			anim_name = "move_down"
		else:
			anim_name = "move_up"

	if is_moving:
		if animated_sprite.animation != anim_name or not animated_sprite.is_playing():
			animated_sprite.play(anim_name)
	else:
		animated_sprite.stop()
		animated_sprite.animation = anim_name
		animated_sprite.frame = animated_sprite.sprite_frames.get_frame_count(anim_name) - 1

func _on_pantoon_body_entered(body: Node2D) -> void:
	if body == self:
		max_speed = slow_speed
		velocity = velocity.limit_length(slow_speed)


func _on_pantoon_body_exited(body: Node2D) -> void:
	if body == self:
		max_speed = normal_speed

func _on_fuel_empty():
	velocity = Vector2.ZERO
	max_speed = 0
	get_tree().current_scene.timer_running = false
	get_tree().current_scene.game_over_screen.show_screen()
	print("Fuel bitti → Oyun sonlandırıldı.")
