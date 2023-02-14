// code from class wiki
// Require the packages we will use:
const http = require("http"),
    fs = require("fs");

const port = 3456;
const file = "client.html";

// Listen for HTTP connections.  This is essentially a miniature static file server that only serves our one file, client.html, on port 3456:
const server = http.createServer(function (req, res) {
    // This callback runs when a new connection is made to our HTTP server.

    fs.readFile(file, function (err, data) {
        // This callback runs when the client.html file has been read from the filesystem.

        if (err) return res.writeHead(500);
        res.writeHead(200);
        res.end(data);
    });
});
server.listen(port);

// Import Socket.IO and pass our HTTP server object to it.
const socketio = require("socket.io")(http, {
    wsEngine: 'ws'
});


// Attach our Socket.IO server to our HTTP server to listen
const io = socketio.listen(server);
let userlist = []; //all users connected
let roomlist = []; //all users
roomlist.push({name: "Main Room", pwd: "", creator: [], ban:[]});
io.sockets.on("connection", function (socket) {
    // This callback runs when a new Socket.IO connection is established.

    //check disconnected learn from https://stackoverflow.com/questions/20007453/how-can-i-detect-disconnects-on-socket-io/20007679
    socket.on('disconnect', function(){
        
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                let room = userlist[i].roomnow;
                let name = userlist[i].name;
                userlist.splice(i,1);
                
                io.in(room).emit("show_user_list", {user_list: userlist, current_room: room});
                io.in(room).emit("message_to_client", { message: name + " is off-line." })
            }
        }

        for(let j in roomlist){
            for(let k in roomlist[j].ban){
                if(roomlist[j].ban[k]==socket.id){
                    roomlist[j].ban.splice(k,1);
                }
            }

            for(let l in roomlist[j].creator){
                if(roomlist[j].creator[l]==socket.id){
                    roomlist[j].creator.splice(l,1);
                    if(roomlist[j].creator.length == 0){
                        for (let m in userlist){
                            if(userlist[m].roomnow == roomlist[j].name){
                                roomlist[j].creator.push(userlist[m].id);
                                io.to(userlist[m].id).emit("privilege",{boolean:true});
                                break;
                            }
                        }
                    }
                }
            }
        }
        
    });

   

    //add new user to the userlist
    socket.on('username', function(data){
        for (let item in userlist){
            if (userlist[item].name == data["username"]){
                io.to(socket.id).emit("new_user_status",{success:false, alert:"The nickname is taken by others"});
                return;
            }else if(userlist[item].id == socket.id){
                io.to(socket.id).emit("new_user_status",{success:false, prev: true, prevname: userlist[item].name, alert:"You have already logged in and have a nickname"});
                return;
            }

        }

        const newuser = {name: data["username"], id: socket.id, roomnow: "Main Room"};
        userlist.push(newuser);
        console.log(userlist);
        socket.join("Main Room");
        console.log("User joins the default main room");
        io.in("Main Room").emit("message_to_client", { message: data["username"]+" has joined the Main Room." })
        io.to(socket.id).emit("new_user_status",{success:true, alert:"Login in success"});
        //update room_list
        io.emit("show_room_list", {room_list: roomlist});
        //update user_list
        io.in("Main Room").emit("show_user_list", {user_list: userlist, current_room: "Main Room"});

    });

    //add new room to the roomlist
    socket.on('create_room', function(data){
        for (let i in roomlist){
            if (roomlist[i].name == data["room"]){
                io.to(socket.id).emit("new_room_status",{success:false, alert:"The roomname is already in used"});
                return;
            }
        }

        const newroom = {name: data['room'], pwd: data['pass'], creator: [socket.id], ban:[]};
        roomlist.push(newroom);
        console.log(roomlist);
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                let curroom = userlist[i].roomnow;
                userlist[i].roomnow = data['room'];
                socket.leave(curroom);
                io.in(curroom).emit("show_user_list", {user_list: userlist, current_room: curroom});
                io.in(curroom).emit("message_to_client", { message: userlist[i].name + " leaves this room." })
                socket.join(data['room']);
                io.in(userlist[i].roomnow).emit("show_user_list", {user_list: userlist, current_room: userlist[i].roomnow});
                io.in(userlist[i].roomnow).emit("message_to_client", { message: userlist[i].name + " joined Room: " +  data['room']})
                console.log(data['room']+" is created successfully!");
            }
        }
        
        //admin 
        io.to(socket.id).emit("privilege",{boolean:true});
        
        
        io.to(socket.id).emit("new_room_status",{success:true, alert:"create success"});
        //update room_list
        io.emit("show_room_list", {room_list: roomlist});
        
        

    });

    //join a room
    socket.on('join_room', function(data){
        let exist = false;
        let room = null;
        for (let i in roomlist){
            if (roomlist[i].name == data["room"]){
                room = roomlist[i];
                exist = true;
            }
        }
        if(!exist){
            io.to(socket.id).emit("join_room_status",{success:false, alert:"The roomname is not valid or doesn't exist. Please check again!"});
            return;
        }

        if(room.pwd != "" && data['pass'] != room.pwd){
            io.to(socket.id).emit("join_room_status",{success:false, alert:"The room is a private room and your password entered is not correct. Please check again!"});
            return;
        }

        for(let k in room.ban){
            if (socket.id == room.ban[k]){
                io.to(socket.id).emit("join_room_status",{success:false, alert:"You're banned from this room!"});
                return;
            }
        }

        
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                let curroom = userlist[i].roomnow;
                if(curroom == data['room']){
                    io.to(socket.id).emit("join_room_status",{success:false, alert:"You're in the same room."});
                    return;
                }
                userlist[i].roomnow = data['room'];
                socket.leave(curroom);
                io.in(curroom).emit("show_user_list", {user_list: userlist, current_room: curroom});
                io.in(curroom).emit("message_to_client", { message: userlist[i].name + " leaves this room." })
                socket.join(data['room']);
                io.in(userlist[i].roomnow).emit("show_user_list", {user_list: userlist, current_room: userlist[i].roomnow});
                io.in(userlist[i].roomnow).emit("message_to_client", { message: userlist[i].name + " joined Room: " +  data['room']})
                console.log(data['room']+" joined successfully!");
            }


        }
        
        //admin 
        let pr = false;
        for(let j in room.creator){
            if (socket.id == room.creator[j]){
                pr = true;
            }
        }
        io.to(socket.id).emit("privilege",{boolean:pr});
        //update room_list
        io.emit("show_room_list", {room_list: roomlist});
        io.to(socket.id).emit("join_room_status",{success:true, alert:"create success"});
        
    });

    //leave room 
    socket.on("leave_room", function(data){
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                let curroom = userlist[i].roomnow;
                userlist[i].roomnow = "Main Room";
                socket.leave(curroom);
                io.in(curroom).emit("show_user_list", {user_list: userlist, current_room: curroom});
                io.in(curroom).emit("message_to_client", { message: userlist[i].name + " leaves this room." })
                socket.join("Main Room");
                io.in(userlist[i].roomnow).emit("show_user_list", {user_list: userlist, current_room: userlist[i].roomnow});
                io.in(userlist[i].roomnow).emit("message_to_client", { message: userlist[i].name + " joined Main Room"})
                console.log("Leaves successfully!");
            }


        }
        io.to(socket.id).emit("privilege",{boolean:false});
    });
    //kick user out
    socket.on("kick_room", function(data){
        let cuser = null;
        let target = null;
        for(let a in userlist){
            if(userlist[a].id == socket.id){
                cuser = userlist[a];
            }       
            if(userlist[a].name == data['user']){
                target = userlist[a];
            }
        
        }

        if(target == null){
            io.to(socket.id).emit("kick_status",{success:false, alert:"The user you entered does not exist / invalid"});
            return;
        }

        if(target == cuser){
            io.to(socket.id).emit("kick_status",{success:false, alert:"You can't kick out yourself. Please use the Leave Room button"});
            return;
        }

        if(target.roomnow != cuser.roomnow){
            io.to(socket.id).emit("kick_status",{success:false, alert:"The username you entered is not in the same room with you. You can't kick out the user."});
            return;
        }
        
        let curroom = target.roomnow;
        target.roomnow = "Main Room";
        io.sockets.sockets.get(target.id).leave(curroom);
        io.in(curroom).emit("show_user_list", {user_list: userlist, current_room: curroom});
        io.in(curroom).emit("message_to_client", { message: target.name + " leaves this room." })
        io.sockets.sockets.get(target.id).join("Main Room");
        io.in(target.roomnow).emit("show_user_list", {user_list: userlist, current_room: target.roomnow});
        io.in(target.roomnow).emit("message_to_client", { message: target.name + " joined Main Room"})
        console.log("Kicks successfully!");
        io.to(target.id).emit("privilege",{boolean:false});
        io.to(target.id).emit("message_to_client", { message:"You're kicked out from "+ curroom+ " by the admin. Back to the Main Room now."});
        io.to(socket.id).emit("kick_status",{success:true});
    });

    //add user as admin
    socket.on("admin_room", function(data){
        let cuser = null;
        let target = null;
        let croom = null;
        for(let a in userlist){
            if(userlist[a].id == socket.id){
                cuser = userlist[a];
            }       
            if(userlist[a].name == data['user']){
                target = userlist[a];
            }
            
        }

        if(target == null){
            io.to(socket.id).emit("admin_status",{success:false, alert:"The user you entered does not exist / invalid"});
            return;
        }

        if(target == cuser){
            io.to(socket.id).emit("admin_status",{success:false, alert:"You can't add yourself as admin."});
            return;
        }
        croom = cuser.roomnow;
        for(let b in roomlist){
            if(roomlist[b].name == croom){
                for (let c in roomlist[b].ban){
                    if(roomlist[b].ban[c] == target.id){
                        io.to(socket.id).emit("admin_status",{success:false, alert:"This user is banned from the room."});
                        return;
                    }
                }

                for (let d in roomlist[b].creator){
                    if(roomlist[b].creator[d] == target.id){
                        io.to(socket.id).emit("admin_status",{success:false, alert:"The user is already an administrator."});
                        return;
                    }
                }
                roomlist[b].creator.push(target.id);
                
                
            }    
            
        }
        if(target.roomnow == cuser.roomnow){
            io.to(target.id).emit("privilege",{boolean:true});
        }
        io.to(socket.id).emit("admin_status",{success:true});


    });
    //ban user 
    socket.on("ban_room", function(data){
        let cuser = null;
        let target = null;
        let croom = null;
        for(let a in userlist){
            if(userlist[a].id == socket.id){
                cuser = userlist[a];
            }       
            if(userlist[a].name == data['user']){
                target = userlist[a];
            }
        
        }

        if(target == null){
            io.to(socket.id).emit("ban_status",{success:false, alert:"The user you entered does not exist / invalid"});
            return;
        }

        if(target == cuser){
            io.to(socket.id).emit("ban_status",{success:false, alert:"You can't ban yourself."});
            return;
        }

        croom = cuser.roomnow;
        for(let b in roomlist){
            if(roomlist[b].name == croom){
                for (let c in roomlist[b].ban){
                    if(roomlist[b].ban[c] == target.id){
                        io.to(socket.id).emit("ban_status",{success:false, alert:"You have already banned this user."});
                        return;
                    }
                }

                for (let d in roomlist[b].creator){
                    if(roomlist[b].creator[d] == target.id){
                        io.to(socket.id).emit("ban_status",{success:false, alert:"You can't banned an administrator."});
                        return;
                    }
                }
                roomlist[b].ban.push(target.id);
            }    
        }

        if(target.roomnow == cuser.roomnow){
            let curroom = target.roomnow;
            target.roomnow = "Main Room";
            io.sockets.sockets.get(target.id).leave(curroom);
            io.in(curroom).emit("show_user_list", {user_list: userlist, current_room: curroom});
            io.in(curroom).emit("message_to_client", { message: target.name + " leaves this room." })
            io.sockets.sockets.get(target.id).join("Main Room");
            io.in(target.roomnow).emit("show_user_list", {user_list: userlist, current_room: target.roomnow});
            io.in(target.roomnow).emit("message_to_client", { message: target.name + " joined Main Room"})
            console.log("Banned successfully!");
            io.to(target.id).emit("privilege",{boolean:false});
            io.to(target.id).emit("message_to_client", { message:"You're banned from "+ curroom+ " by the admin. Back to the Main Room now."});
            
        }
    
        io.to(socket.id).emit("ban_status",{success:true});
        
        
    });

    socket.on('message_to_server', function (data) {
        // This callback runs when the server receives a new message from the client.
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                console.log("message: " + userlist[i].name+": "+data["message"]+" in "+ userlist[i].roomnow); // log it to the Node.JS output
                io.in(userlist[i].roomnow).emit("message_to_client", { message: userlist[i].name+": "+data["message"] }) // broadcast the message to other users
            }
        }    
        

        
    });

    socket.on('delete_room',function(data){
        let curroom = null;
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                curroom = userlist[i].roomnow;
            }

        }

        for(let l in userlist){
            if(userlist[l].roomnow == curroom){
                userlist[l].roomnow = "Main Room";
                io.sockets.sockets.get(userlist[l].id).leave(curroom);
                io.sockets.sockets.get(userlist[l].id).join("Main Room");
                io.to(userlist[l].id).emit("message_to_client", { message: "Room: "+curroom+" is deleted by the admin. Back to the Main Room now."});
                
                io.to(userlist[l].id).emit("privilege",{boolean:false});
            }
        }

        for(let j in roomlist){
            if(curroom == roomlist[j].name){
                roomlist.splice(j,1);
            }
        }

        io.in("Main Room").emit("show_user_list", {user_list: userlist, current_room: "Main Room"});
        io.emit("show_room_list", {room_list: roomlist});
             
        
        
    });
    socket.on('private_message', function (data) {
        let msg = null;
        if(data['target']==socket.id){
            io.to(socket.id).emit("pv_status",{success:false, alert:"You can't send a private message to yourself"});
            return;
        }
        for (let i in userlist){
            if(userlist[i].id == socket.id){
                msg = "Private message from "+userlist[i].name+" to "; 
                io.in(userlist[i].roomnow).emit("show_user_list", {user_list: userlist, current_room: userlist[i].roomnow});
            }
        }    

        for (let j in userlist){
            if(userlist[j].id == data['target']){
                msg += userlist[j].name+ " : "+ data['message']; 
            }
        }   
        
        io.to(socket.id).emit("message_to_client", {message: msg});
        io.to(data['target']).emit("message_to_client", {message: msg});
        
    });
});
console.log("listening on port 3456, serving chat");