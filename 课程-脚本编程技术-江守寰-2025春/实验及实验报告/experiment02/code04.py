from PIL import Image

# 打开原始图片
image = Image.open("penguin.jpg")

# 打开水印图片
watermark = Image.open("logo.png")
scale = 0.3
new_width = int(watermark.width * scale)
new_height = int(watermark.height * scale)
watermark = watermark.resize((new_width, new_height))

# 获取原始图片的宽度和高度
width, height = image.size

# 创建一个新的图像对象，用于叠加水印
watermarked_image = image.copy()

# 计算水印位置（通常在右下角）
margin = 10
position = (width - watermark.width - margin, height - watermark.height - margin)

# 叠加水印
watermarked_image.paste(watermark, position, watermark)

# 保存带水印的图片
watermarked_image.save("watermarked_image.jpg")

# 显示图片
watermarked_image.show()

