def go a, b
  res = []
  for i in 0..(a.length)
    if a[i] != b[i]
      res.push i
    end
  end

  return res
end

n, m = gets.strip.split.map &:to_i
a = gets.strip
b = gets.strip

res = *(1..n)
for i in 0..(m-n)
  curr = go(a, b[i..i+n-1]).map{ |x| x + 1 }
  if curr.length < res.length
    res = curr
  end
end

print res.length.to_s + "\n"
res.each{ |x| print x.to_s + " " }
print "\n"
