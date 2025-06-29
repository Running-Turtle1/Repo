import jieba

with open('comment.txt', 'r', encoding = 'utf-8') as f:
    text = f.read()

word = jieba.lcut(text)

word = [
    y for y in [x.strip() for x in word if x.strip()] if y not in set('，。、！？；（）“”\n')
]

word_dict = {}
for w in word:
    if w in word_dict:
        word_dict[w] += 1
    else:
        word_dict[w] = 1

for x, y in sorted(word_dict.items(), key = lambda item: item[1], reverse = True):
    print(x, y)


