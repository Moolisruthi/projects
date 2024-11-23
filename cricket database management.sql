import mysql.connector as mycon
 
con = mycon.connect(host='localhost', user='root', password="user")
cur = con.cursor()
 
cur.execute("CREATE DATABASE IF NOT EXISTS cricket")
cur.execute("USE cricket")
 
cur.execute("""
    CREATE TABLE IF NOT EXISTS players (
        player_id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(50),
        team VARCHAR(50),
        runs INT,
        wickets INT )""")
con.commit()
 
choice = None
while choice != 0:
    print("1. ADD RECORD")
    print("2. DELETE RECORD")
    print("3. UPDATE RECORD")
    print("4. SEARCH RECORD")
    print("5. DISPLAY RECORD")
    print("0. EXIT")
    choice = int(input("Enter Choice: "))
 
    if choice == 1:
        name = input("Enter Player Name: ")
        team = input("Enter Team: ")
        runs = int(input("Enter Runs: "))
        wickets = int(input("Enter Wickets: "))
        query = "INSERT INTO players (name, team, runs, wickets) VALUES (%s, %s, %s, %s)"
        cur.execute(query, (name, team, runs, wickets))
        con.commit()
        print("## Data Saved ##")
 
    elif choice == 2:
        player_id = int(input("Enter Player ID to Delete: "))
        query = "DELETE FROM players WHERE player_id = %s"
        cur.execute(query, (player_id,))
        con.commit()
        if cur.rowcount > 0:
            print("## Record Deleted ##")
        else:
            print("## No Record Found with Given Player ID ##")
 
    elif choice == 3:
        player_id = int(input("Enter Player ID to Update: "))
        query = "SELECT * FROM players WHERE player_id = %s"
        cur.execute(query, (player_id,))
        if cur.fetchone():
            name = input("Enter New Name: ")
            team = input("Enter New Team: ")
            runs = int(input("Enter New Runs: "))
            wickets = int(input("Enter New Wickets: "))
            query = "UPDATE players SET name = %s, team = %s, runs = %s, wickets = %s WHERE player_id = %s"
            cur.execute(query, (name, team, runs, wickets, player_id))
            con.commit()
            print("## Record Updated ##")
        else:
            print("## No Record Found with Given Player ID ##")
 
    elif choice == 4:
        search_term = input("Enter Player Name or Team to Search: ")
        query = "SELECT * FROM players WHERE name LIKE %s OR team LIKE %s"
        cur.execute(query, ('%' + search_term + '%', '%' + search_term + '%'))
        result = cur.fetchall()
        if result:
            print("%10s" % "PLAYER ID", "%20s" % "NAME", "%20s" % "TEAM", "%10s" % "RUNS", "%10s" % "WICKETS")
            for row in result:
                print("%10s" % row[0], "%20s" % row[1], "%20s" % row[2], "%10s" % row[3], "%10s" % row[4])
        else:
            print("## No Records Found ##")
 
    elif choice == 5:
        query = "SELECT * FROM players"
        cur.execute(query)
        result = cur.fetchall()
        print("%10s" % "PLAYER ID", "%20s" % "NAME", "%20s" % "TEAM", "%10s" % "RUNS", "%10s" % "WICKETS")
        for row in result:
            print("%10s" % row[0], "%20s" % row[1], "%20s" % row[2], "%10s" % row[3], "%10s" % row[4])
 
    elif choice == 0:
        con.close()
        print("## Bye!! ##")
 
    else:
        print("## INVALID CHOICE ##")
