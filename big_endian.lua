-- 2 Byte Big Endian
function BE2BytesToValue(b1, b2)
	return
		(b1 << 8) |
		 b2
end

function BE2ValueToBytes(val)
	val = val & 0xFFFF
	local b1 = (val >> 8) & 0xFF
	local b2 = val & 0xFF
	return b1, b2
end

local BE2Type = registerCustomTypeLua(
	"2 Byte Big Endian",
	2,
	BE2BytesToValue,
	BE2ValueToBytes
)

-- 4 Byte Big Endian
function BE4BytesToValue(b1, b2, b3, b4)
	return
		(b1 << 24) |
		(b2 << 16) |
		(b3 << 8 ) |
		 b4
end

function BE4ValueToBytes(val)
	val = val & 0xFFFFFFFF
	local b1 = (val >> 24) & 0xFF
	local b2 = (val >> 16) & 0xFF
	local b3 = (val >> 8 ) & 0xFF
	local b4 = val & 0xFF
	return b1, b2, b3, b4
end

local BE4Type = registerCustomTypeLua(
	"4 Byte Big Endian",
	4,
	BE4BytesToValue,
	BE4ValueToBytes
)

-- Float Big Endian
function FloatBE_BytesToValue(b1,b2,b3,b4)
	return byteTableToFloat({
		b4, b3, b2, b1
	})
end

function FloatBE_ValueToBytes(value)
	local t = floatToByteTable(value)
	return t[4], t[3], t[2], t[1]
end

registerCustomTypeLua(
	"Float Big Endian",
	4,
	FloatBE_BytesToValue,
	FloatBE_ValueToBytes
)
