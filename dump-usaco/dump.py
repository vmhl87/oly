import requests

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:122.0) Gecko/20100101 Firefox/122.0',
    'Accept': '*/*',
    'Accept-Language': 'en-US,en;q=0.5',
    'X-Discord-Locale': 'en-US',
    'X-Discord-Timezone': 'America/New_York',
    'Connection': 'keep-alive',
    'Sec-Fetch-Dest': 'empty',
    'Sec-Fetch-Mode': 'cors',
    'Sec-Fetch-Site': 'same-origin'
}

for i in range(487, 1431):
    res = requests.get(
            "https://usaco.org/index.php?page=viewproblem2&cpid=" + str(i),
            headers=headers
        )
    if "h2" not in res.text: continue
    title = res.text.split("<h2> ")[1].split(" </h2>")[0]
    title = title.lower().replace('usaco ', '').replace(' contest,', '')
    name = res.text.split("<h2> ")[2].split(" </h2>")[0].lower().replace('.', '')
    print("processing " + title + ' ' + ' '.join(name.split(' ')[:2]))
    f = open("html/" + title + " " + name + ".html", 'w')
    re = res.text.replace("https://d3js.org/d3.v3.min.js", "current/js/d3.v3.min.js")
    # re = re.replace("https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-AMS-MML_HTMLorMML", "current/js/MathJax.js")
    f.write(re)
    f.close()
