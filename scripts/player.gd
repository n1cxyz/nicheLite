extends CharacterBody2D

@export var speed := 100.0

var last_direction := Vector2.DOWN  # Default facing direction

func _physics_process(delta):
	var input_vector = Vector2.ZERO
	input_vector.x = Input.get_action_strength("ui_right") - Input.get_action_strength("ui_left")
	input_vector.y = Input.get_action_strength("ui_down") - Input.get_action_strength("ui_up")
	input_vector = input_vector.normalized()

	# Movement
	velocity = input_vector * speed
	move_and_slide()

	# Update direction if moving
	if input_vector != Vector2.ZERO:
		last_direction = input_vector
		play_run_animation(input_vector)
	else:
		play_idle_animation(last_direction)


func play_run_animation(direction: Vector2):
	var anim_name = ""

	if abs(direction.x) > abs(direction.y):
		anim_name = "Run_Right" if direction.x > 0 else "Run_Left"
	else:
		anim_name = "Run_Down" if direction.y > 0 else "Run_Up"

	if $AnimatedSprite2D.animation != anim_name:
		$AnimatedSprite2D.play(anim_name)


func play_idle_animation(direction: Vector2):
	if direction == null:
		direction = Vector2.DOWN
		
	var anim_name = ""

	if abs(direction.x) > abs(direction.y):
		anim_name = "Idle_Right" if direction.x > 0 else "Idle_Left"
	else:
		anim_name = "Idle_Down" if direction.y > 0 else "Idle_Up"

	if $AnimatedSprite2D.animation != anim_name:
		$AnimatedSprite2D.play(anim_name)
