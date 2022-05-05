# Message with information for a dish of pasta

# The topic pub/sub flow would be as follows:
# Customer -> 'pasta_order' -> Waiter
# Waiter -> 'pasta_cook' -> Chef

uint64 timestamp          # time since system start (microseconds)

uint16 customer_table_id  # customer’s table ID to know where to serve

uint8 menu_name           # menu, e.g. Carbonara, Amatriciana
uint8 cooked_texture      # how cooked the pasta should be, e.g. Al Dente
uint8 pasta_type          # type of pasta, e.g. Spaghetti, Lasagna, Rigatoni
float32 pasta_temperature # temperature of the pasta in degrees Celsius

# TOPICS pasta_cook pasta_order
