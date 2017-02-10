function math.round(num)
    return math.floor(num + 0.5)
end

function math.ToBinary(intValue)
    local arr = {}
    --解析成二进制数字
    assert(intValue >=0,"数据要大于0")
    while intValue ~= 0 do
        local x = intValue%2
        table.insert(arr,x)
        intValue = math.floor(intValue/2)
    end

    for i=#arr+1,64 do
        table.insert(arr,0)
    end
    return arr
end

function math.fromBinaryToDec(arr)
    local val = 0
    for i=1,#arr do
        val = val+arr[i]*math.pow(2,i-1)
    end
    return val
end

function math.randseed()
    math.randomseed(tonumber(tostring(os.time()):reverse():sub(1,6)))
end