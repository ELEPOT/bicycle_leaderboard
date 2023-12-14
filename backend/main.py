import pygsheets as sheet
from flask import Flask, render_template
from HTMLTable import HTMLTable

app = Flask(__name__)


@app.route("/")
def leaderboard():
    i = 1
    gc = sheet.authorize(service_file='auth/bicyclemileagedatabase-e9a752e9691d.json')
    url = 'https://docs.google.com/spreadsheets/d/1ANhQHgFkB4Ce9WfsSZ4gT-u6YW7g4n33WO7UtMNWouI/edit#gid=861705765'
    sht = gc.open_by_url(url)
    wks = sht[0]

    total_distances = {}

    for row in wks:
        distance = row[2]
        card_id = row[1]

        if distance == '' or card_id == '':
            print('STOP')
            break

        else:
            if card_id not in total_distances.keys():
                total_distances[card_id] = float(distance)
            else:
                total_distances[card_id] += float(distance)

        i += 1

    total_distances = list(total_distances.items())

    total_distances.sort(key=lambda elem: elem[1], reverse=True)

    table = HTMLTable(caption='共享單車排行榜')

    table.append_header_rows([('名次', '卡號', '距離 (m)')])

    print(total_distances)

    for ranking, (card_id, distance) in enumerate(total_distances):
        table.append_data_rows([(ranking + 1, card_id, distance)])

    return render_template('index.html', table=table.to_html())


if __name__ == '__main__':
    app.run()
