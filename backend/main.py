# 匯入所需模組
import pygsheets as sheet
from flask import Flask, render_template, request
from HTMLTable import HTMLTable
app = Flask(__name__)
# 以下函式會在使用者訪問網站時呼叫


def get_sorted_total_distance():
    i = 1
    # 開啟 Google 表單
    gc = sheet.authorize(service_file='auth/bicyclemileagedatabase-e9a752e9691d.json')
    url = 'https://docs.google.com/spreadsheets/d/1ANhQHgFkB4Ce9WfsSZ4gT-u6YW7g4n33WO7UtMNWouI/edit#gid=861705765'
    sht = gc.open_by_url(url)
    wks = sht[0]

    total_distances = {}

    # 把同卡號的里程數加起來，直到讀到表單最後一行為止
    for row in wks:
        distance = row[2]
        card_id = row[1]

        if distance == '' or card_id == '':
            break

        else:
            if card_id not in total_distances.keys():
                total_distances[card_id] = float(distance)
            else:
                total_distances[card_id] += float(distance)

        i += 1

    # 將每個卡號的總里程數從大到小排列
    total_distances = list(total_distances.items())
    total_distances.sort(key=lambda elem: elem[1], reverse=True)

    return total_distances


@app.route("/")
def leaderboard():
    total_distances = get_sorted_total_distance()

    # 將卡號與里程數轉換成 html 表格
    table = HTMLTable(caption='共享單車排行榜')

    table.append_header_rows([('名次', '卡號', '距離 (m)')])

    for ranking, (card_id, distance) in enumerate(total_distances):
        table.append_data_rows([(ranking + 1, card_id, round(distance))])
    # 將 html 表格回傳給使用者
    return render_template('index.html', table=table.to_html())


@app.route("/data/send/")
def get_ranking():
    total_distances = get_sorted_total_distance()
    for ranking, (card_id, distance) in enumerate(total_distances):
        if card_id == request.args.get('id'):
            return str(ranking + 1)

    raise f"Cannot get ranking of {request.args.get('id')}"


# 開始伺服器
if __name__ == '__main__':
    app.run()
