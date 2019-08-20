.PHONY: clean All

All:
	@echo "----------Building project:[ BrownMovement - Debug ]----------"
	@"$(MAKE)" -f  "BrownMovement.mk"
clean:
	@echo "----------Cleaning project:[ BrownMovement - Debug ]----------"
	@"$(MAKE)" -f  "BrownMovement.mk" clean
