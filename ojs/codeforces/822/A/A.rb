def fact (x)
  return x == 0 ? 1 : fact(x-1) * x
end

print fact(gets.strip.split.map(&:to_i).min).to_s + "\n"

