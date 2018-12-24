

function function1()
    print('function1')
end



function run()
    a = vec3.new(8, 4, 2)
    b = vec3.new(1, 2, 1)
    result = a - b

    print(result.x, result.y, result.z)

    print(playerTransform.position.x, playerTransform.position.y, playerTransform.position.z)

    playerTransform.position = vec3.new(0, -3, 0)
    playerTransform.scale = vec3.new(0.04, 0.02, 0.05)
end


