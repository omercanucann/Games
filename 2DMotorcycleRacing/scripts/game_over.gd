extends CanvasLayer

func show_screen():
	visible = true

func _on_RestartButton_pressed():
	get_tree().reload_current_scene()


func _on_button_pressed() -> void:
	get_tree().reload_current_scene()
