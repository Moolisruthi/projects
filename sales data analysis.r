# Load necessary libraries
library(tidyverse)

# 1: Analyze sales data from a CSV file and calculate total sales for each product
sales_data <- read_csv("sales_data.csv")

total_sales <- sales_data %>%
  group_by(Product) %>%
  summarize(Total_Sales = sum(Sales))

# 2: Identify the top N products with the highest total sales
top_n_products <- total_sales %>%
  arrange(desc(Total_Sales)) %>%
  top_n(10)  # Change the number to display more or fewer top products

# 3: Analyze the distribution of total sales and create a histogram
ggplot(total_sales, aes(x = Total_Sales)) +
  geom_histogram(binwidth = 1000, fill = "blue", color = "black") +
  labs(title = "Distribution of Total Sales",
       x = "Total Sales",
       y = "Frequency")

# Generate bar chart for top N products
ggplot(top_n_products, aes(x = reorder(Product, Total_Sales), y = Total_Sales)) +
  geom_bar(stat = "identity", fill = "orange") +
  coord_flip() +  # Flip the coordinates to display horizontal bars
  labs(title = "Top Products by Total Sales",
       x = "Product",
       y = "Total Sales")
