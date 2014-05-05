#-*- coding:utf-8 -*-
'''
G  is the attack graph that generated by this tool
H  is the temp set of parent set of current state

'''
import xml.etree.ElementTree as ET
import networkx as nx
import json
import HostPrilvage as Priv
import string

#读取xml文件
def xmlpython(xml1,n):
    xml2=open(xml1).read()
    G=create_graph(xml2,n)  
    return G

def create_graph(xml1,n):
    G=nx.DiGraph()                      #创建有向图      
    H=nx.DiGraph()                      #创建存储父节点的图
    root=ET.fromstring(xml1)            #获取xml的根节点
    G=first_node(G,root)                #存储第一个点
                                        #i=1 This place is no need of var.
    ip1=G.node[1]['host_ip']
    com1=G.node[1]['prilvage']
    G=post_node(G,H,1,root,n)
    return G

def post_node(G,H,i,root,n):
    attack_init_node_code=i
    f=file("Network_link.json")
    net_link=json.load(f)
                                                                 		#ip2=G.node[i]['host_ip']
    current_ip=G.node[i]['host_ip']
    current_priv=G.node[i]['prilvage']
    current_connection=net_link[current_ip]
    
    '''
    print current_connection
    	Test the current string has loaded succesully!
    '''
    H.add_node(i,host_ip=current_ip,prilvage=current_priv)       		#将自身当做父节点存入H图中
    for vid1 in root.findall('./vid'):                           		#遍历vid元素，查找ip
        lenH=H.nodes()
        if len(lenH)>string.atoi(n)-1:                                      #判断父节点个数是否超过限定    
            break
        compare_ip=vid1.get('ip')                                       	#获取vid的ip
        ''' 
        Judge the current_ip in current_connection to guarantee the connection
        of the current connection
        '''
        if (compare_ip in current_connection):
            '''print "YES IN IT" '''
            for attack1 in vid1.findall('./attack'):                 		#遍历attack元素，查找攻击
                break_flag=0
                c=0
                pr1=attack1.find('./pr').text
                compare_priv=attack1.find('./post').text

                for x in H.nodes():                                   		#如果后果点在父节点中，就返回
                    if H.node[x]['host_ip']==compare_ip and compare_priv in H.node[x]['prilvage']:
                        break_flag=1
                        break
                if break_flag==1:
                    continue
        '''
            Nodes are already in the Attack Graph,we just establish new attack path
            Attack edge into the exist edge
            Start:
        '''
                for x in G.nodes():                                   		#如果后果点在G图中，就直接建立边
                    if G.node[x]['host_ip']==compare_ip and compare_priv in G.node[x]['prilvage']:
                        G.add_edge(attack_init_node_code,x,pr=pr1)
                        c=1
                        break

                if c==1:
                    continue
        '''
            End
        '''
        '''
        If no nodes or edges is exist we establish new nodes into G and new edges
        into Edges
        Start:
        '''
                else:
                
                    if compare_priv=='root':
                        current_priv=Priv.root_priv
                    elif compare_priv=='user':
                        current_priv=Priv.user_priv
                    elif compare_priv=='login':
                        current_priv=Priv.login_priv
                    elif compare_priv=='access':
                        current_priv=Priv.access_priv
                
                    G.add_node(i+1,host_ip=compare_ip,prilvage=current_priv)
                    G.add_edge(attack_init_node_code,i+1,pr=pr1)
                    i=i+1
                    
                    G=post_node(G,H,i,root,n)
        '''
            End
        '''
    '''Remove all the node of The parent nodes'''                                
    H.remove_node(attack_init_node_code)
    return G

#输入第一个攻击点
def first_node(G1,root):
    attacker_ip='192.168.1.101'              #attacker's host ip
    attacker_pr='0.5'                        #attacker's attack probilities
    attacker_priv=Priv.root_priv             #attacker's Current Prilvage of it's own initial PC

    '''
    #判断权限包含关系
    if post1=='root':
        post1=['root','user','login','access']
    if post1=='user':
        post1=['user','login','access']
    if post1=='login':
        post1=['login','access']
    if post1=='access':
        post1=['access']
    '''
    G1.add_node(1,host_ip=attacker_ip,prilvage=attacker_priv)
    return G1
    
def main(argv):
    '''
    f=file("Network_link.json")
    net_link=json.load(f)
    
    '''
    
    ''' Load Json File of Netork topology & Test all of this is OK
	Test the json load of network topology is ok for all the 
	things in this area

    print net_link
    print "network_keys"
    print net_link.keys()
    print "network_link 0f 192.168.1.1"
    print net_link["192.168.1.101"]
    test_list=net_link["192.168.1.101"]
    compare_string=test_list[1].encode("utf-8")
    if(test_list[1]=='192.168.1.103'):
	print ""	
	print "YES"
	print ""
    else:
	print "ERROR ERROR ERROR"
	print test_list[1]

    '''	
    '''n=raw_input('输入单一路径的最大节点数：')'''
    n=sys.argv[1]
    G=xmlpython('exploit.xml',n)
    
    #way1=raw_input('输入生成G.node的json文件的路径，不包括文件名：')
    f=open('G.node.json','w')
    f.write(json.dumps(G.node,sort_keys=True,indent=4))
    f.close()
    #way2=raw_input('输入生成G.edge的json文件的路径，不包括文件名：')
    f=open('G.edge.json','w')
    f.write(json.dumps(G.edge,sort_keys=True,indent=4))
    f.close()

    print "生成的 G.node:"
    print json.dumps(G.node,sort_keys=True,indent=4)

    print "生成的 G.edge:"
    print json.dumps(G.edge,sort_keys=True,indent=4)
    
if __name__ == '__main__':

    main(sys.argv)