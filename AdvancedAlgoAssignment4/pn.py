def modexp(a, b, n):

    c = 0
    d = 1
    for i in range(31, -1, -1):
    
        c = 2*c
        d = (d*d) % n
        if((b >> i) & 1 == 1):
        
            c += 1
            d = (d*a) % n
        
        
        
        print("c:%d d:%d i: %d bitset: %d" % (c, d, i, b>>i & 1))
        
    
    return d


print(modexp(29205, 50001, 10000000019))