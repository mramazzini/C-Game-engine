def determine_collision_location(square_x, square_y, square_width, square_height, rect_x, rect_y, rect_width, rect_height):
    # Calculate the right and bottom edges of both shapes
    square_right = square_x + square_width
    square_bottom = square_y + square_height
    rect_right = rect_x + rect_width
    rect_bottom = rect_y + rect_height

    if rect_x > square_right:
        return "right"
    if rect_right < square_x:
        return "left"
    if rect_y > square_bottom:
        return "bottom"
    if rect_bottom < square_y:
        return "top"

    # If none of the above conditions are met, they overlap
    return "overlap"

# Example usage:
square_x = 2
square_y = 2
square_width = 4
square_height = 4

rect_x = 1
rect_y = 6
rect_width = 6
rect_height = 2

collision_location = determine_collision_location(square_x, square_y, square_width, square_height, rect_x, rect_y, rect_width, rect_height)
print("Collision Location:", collision_location)